/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:22:43 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/14 20:02:56 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_input(t_command *cmd)
{
    if (cmd->fd_in >= 0)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    else if (cmd->pipe_in)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
}


static void	setup_output(t_command *cmd)
{
    if (cmd->fd_out >= 0)
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }
    else if (cmd->pipe_out)
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
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
    execve(cmd->path, cmd->argv, env_list_to_array(*env_list)); //  change to NULL ? so that the new program inherits the environment of the current process
    ft_putstr_fd("minishell: command not found\n", 2);
    exit_static_status(*env_list, 127); // to do
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

static char *get_env_value(t_env *env_list, char *name)
{
    while (env_list)
    {
        if (ft_strncmp(env_list->name, name) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return (NULL);
}

static char *search_in_path(t_env *env_list, char *cmd)
{
    char **paths;
    char *path;
    char *tmp;
    int i;

    tmp = get_env_value(env_list, "PATH");
    if (!tmp)
        return (NULL);
    paths = ft_split(tmp, ':');
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        tmp = path;
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(path, X_OK) == 0)
        {
            free_array(paths);
            return (path);
        }
        free(path);
        i++;
    }
    free_array(paths);
    return (NULL);
}

static char *find_command_path(t_command *cmd, t_env *env_list)
{
    if (!cmd->argv || !cmd->argv[0])
        return (NULL);
    if (cmd->is_builtin || strchr(cmd->argv[0], '/'))
        return (ft_strdup(cmd->argv[0]));
    return (search_in_path(env_list, cmd->argv[0]));
}

void	execute_command(t_command *cmd, t_env **env_list)
{
    pid_t pid;
    int status;

    while (cmd)
    {
        if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
        {
            ft_putstr_fd("minishell: '': command not found\n", 2);
            exit_static_status(*env_list, 127); // to do
            cmd = cmd->next;
            continue;
        }
        cmd->path = find_command_path(cmd, *env_list);
        if (!cmd->path && !cmd->is_builtin)
        {
            ft_putstr_fd("minishell: command not found\n", 2);
            exit_static_status(*env_list, 127); // To do
            cmd = cmd->next;
            continue;
        }
        if (cmd->is_builtin && !cmd->is_pipe)
            run_builtin(cmd, env_list);
        else
        {
            pid = fork();
            if (pid == 0)
            {
                if (cmd->is_builtin)
                    run_builtin(cmd, env_list);
                else
                    run_external(cmd, env_list);
                exit(0);
            }
        }
        cmd = cmd->next;
    }
    while (wait(&status) > 0)
        if (WIFEXITED(status))
            exit_static_status(*env_list, WEXITSTATUS(status));
}
