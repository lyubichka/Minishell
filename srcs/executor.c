/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:22:43 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:22:45 by veronikalub      ###   ########.fr       */
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
    setup_input(cmd);
    setup_output(cmd);
    execve(cmd->path, cmd->argv, env_list_to_array(*env_list)); // Executes an external program, replacing the current process
    ft_putstr_fd("minishell: execve failed\n", 2);
    exit_static_status(127);
    exit(127);
}

static void handle_parent_process(t_command *cmd, pid_t pid)
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

static void run_builtin(t_command *cmd, t_env **env_list)
{
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
    
    while (cmd)
    {
        if (cmd->is_builtin)
        {
            run_builtin(cmd, env_list);
            return;
        }
        pid = fork(); // creating a child process
        if (pid == -1)
        {
            ft_putstr_fd("minishell: fork error\n", 2);
            exit_static_status(1);
            return;
        }
        if (pid == 0) 
            run_external_command(cmd, env_list);
        else
            handle_parent_process(cmd, pid);
        cmd = cmd->next;
    }
}
