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
    if (cmd->pipe_in != -1)
    {
        dup2(cmd->pipe_in, STDIN_FILENO);
        close(cmd->pipe_in);
    }
    if (cmd->fd_in != -1)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    if (cmd->last_hd_fd != -1)
    {
        dup2(cmd->last_hd_fd, STDIN_FILENO);
        close(cmd->last_hd_fd);
    }
}

static void setup_output(t_command *cmd)
{
    if (cmd->is_pipe)
    {
        close(cmd->pipe_out[0]);
        dup2(cmd->pipe_out[1], STDOUT_FILENO);
        close(cmd->pipe_out[1]);
    }
    if (cmd->fd_out != -1)
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }
}

static void run_external_command(t_command *cmd, t_env **env_list)
{
    setup_input(cmd);
    setup_output(cmd);
    execve(cmd->path, cmd->argv, env_list_to_array(*env_list));
    ft_putstr_fd("minishell: execve failed\n", 2);
    exit(127);
}

static void handle_parent_process(t_command *cmd, t_env **env_list, pid_t pid)
{
    if (cmd->pipe_in != -1)
        close(cmd->pipe_in);
    if (cmd->fd_in != -1)
        close(cmd->fd_in);
    if (cmd->fd_out != -1)
        close(cmd->fd_out);
    if (cmd->is_pipe)
    {
        close(cmd->pipe_out[1]);
        if (cmd->next)
            cmd->next->pipe_in = cmd->pipe_out[0];
        else
            close(cmd->pipe_out[0]);
    }
    waitpid(pid, &exit_static_status(-1), 0);
    update_exit_status(WEXITSTATUS(exit_static_status(-1)), env_list);
}

static void run_builtin(t_command *cmd, t_env **env_list)
{
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        ft_echo(cmd->argv, env_list);
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        ft_cd(cmd->argv, env_list);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        ft_pwd(env_list);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        ft_env(env_list);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        ft_export(cmd->argv, env_list);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        ft_unset(cmd->argv, env_list);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        ft_exit(cmd->argv, env_list);
    else
        ft_putstr_fd("minishell: unknown builtin\n", 2);
}

void execute_command(t_command *cmd, t_env **env_list)
{
    while (cmd)
    {
        if (cmd->is_builtin)
        {
            run_builtin(cmd, env_list);
            return;
        }
        if (cmd->is_pipe)
        {
            if (pipe(cmd->pipe_out) == -1)
            {
                ft_putstr_fd("minishell: pipe error\n", 2);
                update_exit_status(1, env_list);
                return;
            }
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            ft_putstr_fd("minishell: fork error\n", 2);
            update_exit_status(1, env_list);
            return;
        }
        if (pid == 0)
            run_external_command(cmd, env_list);
        else
            handle_parent_process(cmd, env_list, pid);
        cmd = cmd->next;
    }
}
