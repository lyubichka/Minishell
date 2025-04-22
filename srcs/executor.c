/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:07:13 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 21:28:45 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_parent_process(t_command *cmd, pid_t pid)
{
	int	status;

	status = 0;
	if (cmd->fd_in >= 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out >= 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	waitpid(pid, &status, 0);
	init_signal();
	parent_exit_status(status);
}

static void	fork_and_run_builtin(t_command *cmd, t_env **env_list,\
									t_shell *shell_info)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork error\n", 2);
		exit_static_status(1);
		return ;
	}
	if (pid == 0)
	{
		run_builtin(cmd, env_list, shell_info);
		shell_cleanup(shell_info, exit_static_status(127), 1);
	}
	else
		handle_parent_process(cmd, pid);
}

static void	fork_and_execve(t_command *cmd, t_env **env_list,\
								t_shell *shell_info)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork error\n", 2);
		exit_static_status(1);
		return ;
	}
	if (pid == 0)
		run_external_command(cmd, env_list, shell_info);
	else
		handle_parent_process(cmd, pid);
}

void	execute_command(t_command *cmd, t_env **env_list, t_shell *shell_info)
{
	int	needs_fork;

	while (cmd)
	{
		needs_fork = (cmd->fd_in >= 0 || cmd->fd_out >= 0 || cmd->pipe_in
				|| cmd->pipe_out);
		if (cmd->path)
		{
			fork_and_execve(cmd, env_list, shell_info);
		}
		else if (cmd->is_builtin)
		{
			if (needs_fork)
				fork_and_run_builtin(cmd, env_list, shell_info);
			else
				run_builtin_in_parent(cmd, env_list, shell_info);
		}
		cmd = cmd->next;
	}
}
