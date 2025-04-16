/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:07:13 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/16 21:08:17 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void setup_input(t_command *cmd)
{
    if (cmd->fd_in >= 0)
    {
        if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
        {
            ft_putstr_fd("dup2 fd_in", 2);
            exit(1);
        }
        close(cmd->fd_in);
    }
}


static void setup_output(t_command *cmd)
{
    if (cmd->fd_out >= 0)
    {
        if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
        {
            ft_putstr_fd("dup2 fd_out", 2);
            exit(1);
        }
        close(cmd->fd_out);
    }
}

char **env_list_to_array(t_env *env_list)
{
    char       **array;
    int        count;
    t_env      *tmp;
    char       *name_eq;
    char       *full_str; 
    int        i;
    
    i = 0;
    count = 0;
    tmp = env_list;
    while(tmp)
    {
		count++;
		tmp = tmp->next;
    }
    array = malloc((sizeof(char *)) * (count + 1));
    if (!array)
		return (NULL);
	tmp = env_list; // has to be reset, otherwise it wont run the second while loop.
    while (tmp)
    {
		name_eq = ft_strjoin(tmp->name, "=");
		if (!name_eq)
		{
		    while (i > 0)
				free(array[--i]);
            free(array);
			return (NULL);
        }
        full_str = ft_strjoin(name_eq, tmp->value);
        free(name_eq);
        if (!full_str)
        {
			while (i > 0)
				free(array[--i]);
			free(array);
			return (NULL);
	    }
		array[i] = full_str;
		i++;
		tmp = tmp->next;
    }
    array[count] = NULL;
    return (array);
}

static void run_external_command(t_command *cmd, t_env **env_list)
{
    char	**env_array;
	
	env_array = env_list_to_array(*env_list);
	setup_input(cmd);
    setup_output(cmd);
    execve(cmd->path, cmd->argv, env_array); // Executes an external program, replacing the current process
    ft_putstr_fd("minishell: execve failed\n", 2);
	free_split(env_array);
    exit_static_status(127);
    exit(127);
}

static void	handle_parent_process(t_command *cmd, pid_t pid)
{
    int status;

    status = 0;
    if (cmd->fd_in >= 0)
		close(cmd->fd_in);
    if (cmd->fd_out >= 0)
		close(cmd->fd_out);
    waitpid(pid, &status, 0); // waiting for the child process to complete
    if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
		exit_static_status(1);
}

static void	run_builtin(t_command *cmd, t_env **env_list)
{
	setup_input(cmd);
    setup_output(cmd);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
        ft_echo(cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
        ft_cd(cmd->argv, env_list);
    else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
        ft_pwd();
    else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
        ft_env(env_list);
    else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
        ft_export(cmd->argv, env_list);
    else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
        ft_unset(cmd->argv, env_list);
    else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
        ft_exit(cmd->argv);
    else
        ft_putstr_fd("minishell: unknown builtin\n", 2);
}

void execute_command(t_command *cmd, t_env **env_list)
{
    pid_t    pid;
	t_shell		shell_std;
    
    while (cmd)
    {
		if (!cmd->is_pipe)
		{
            if (cmd->is_builtin)
			{	
				shell_std.std_in = dup(STDIN_FILENO);
				shell_std.std_out = dup(STDOUT_FILENO);
				run_builtin(cmd, env_list);
				dup2(shell_std.std_in, STDIN_FILENO);
				dup2(shell_std.std_out, STDOUT_FILENO);
				close(shell_std.std_in);
				close(shell_std.std_out);
			}
			else if (cmd->path)
				run_external_command(cmd, env_list);
            // return;
        }
		else
		{
			pid = fork(); // creating a child process
			if (pid == -1)
			{
				ft_putstr_fd("minishell: fork error\n", 2);
				exit_static_status(1);
				return;
			}
			if (pid == 0)
			{
				if (cmd->is_builtin)
					run_builtin(cmd, env_list);
				else if (cmd->path)
					run_external_command(cmd, env_list);
				else
					return ;
			}
			else
				handle_parent_process(cmd, pid);
		}
		cmd = cmd->next;
    }
}

// void execute_command(t_command *cmd, t_env **env_list)
// {
// 	t_command	*curr = cmd;
// 	int			pipe_fd[2];
// 	// int			prev_fd = -1;
// 	pid_t		pid;
// 	pid_t		pids[256]; // Handle up to 256 processes
// 	int			i = 0;

// 	while (curr)
// 	{
// 		// Create pipe only if needed (next command exists)
// 		if (curr->next && curr->fd_out == -300 && curr->next->fd_in == -300)
// 		{
// 			if (pipe(pipe_fd) == -1)
// 			{
// 				perror("pipe");
// 				exit_static_status(1);
// 				return;
// 			}
// 			curr->fd_out = pipe_fd[1];
// 			curr->pipe_out = 1;
// 			curr->next->fd_in = pipe_fd[0];
// 			curr->next->pipe_in = 1;
// 		}

// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit_static_status(1);
// 			return;
// 		}

// 		if (pid == 0) // CHILD
// 		{
// 			// Setup input: if redirected, use file; else use previous pipe
// 			if (curr->fd_in >= 0)
// 			{
// 				if (dup2(curr->fd_in, STDIN_FILENO) == -1)
// 					exit(1);
// 			}

// 			// Setup output: if redirected, use file; else use pipe write
// 			if (curr->fd_out >= 0)
// 			{
// 				if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
// 					exit(1);
// 			}

// 			// Close unneeded pipe FDs in child
// 			if (curr->fd_in > 2)
// 				close(curr->fd_in);
// 			if (curr->fd_out > 2)
// 				close(curr->fd_out);

// 			if (curr->is_builtin)
// 				run_builtin(curr, env_list);
// 			else
// 				run_external_command(curr, env_list);

// 			exit(0); // just in case
// 		}
// 		else // PARENT
// 		{
// 			pids[i++] = pid;

// 			// Close ends of pipes after forking
// 			if (curr->fd_in > 2)
// 				close(curr->fd_in);
// 			if (curr->fd_out > 2)
// 				close(curr->fd_out);
// 		}

// 		curr = curr->next;
// 	}

// 	// Wait for all processes
// 	for (int j = 0; j < i; j++)
// 		waitpid(pids[j], NULL, 0);
// }