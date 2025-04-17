/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:59:17 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 23:01:23 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_input(t_command *cmd)
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

static void	setup_output(t_command *cmd)
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

void	run_builtin(t_command *cmd, t_env **env_list)
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

void run_external_command(t_command *cmd, t_env **env_list)
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