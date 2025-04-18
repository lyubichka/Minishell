/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:07:13 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/18 17:31:03 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_builtin_in_parent(t_command *cmd, t_env **env_list)
{
	t_shell	shell_std;

	shell_std.std_in = dup(STDIN_FILENO);
	shell_std.std_out = dup(STDOUT_FILENO);
	run_builtin(cmd, env_list);
	dup2(shell_std.std_in, STDIN_FILENO);
	dup2(shell_std.std_out, STDOUT_FILENO);
	close(shell_std.std_in);
	close(shell_std.std_out);
}

static void	handle_parent_process(t_command *cmd, pid_t pid)
{
	int	status;

	status = 0;
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
		exit_static_status(1);
}

static void	fork_and_run_builtin(t_command *cmd, t_env **env_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork error\n", 2);
		exit_static_status(1);
		return ;
	}
	if (pid == 0)
	{
		run_builtin(cmd, env_list);
		exit(0);
	}
	else
		handle_parent_process(cmd, pid);
}

static void	fork_and_execve(t_command *cmd, t_env **env_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork error\n", 2);
		exit_static_status(1);
		return ;
	}
	if (pid == 0)
		run_external_command(cmd, env_list);
	else
		handle_parent_process(cmd, pid);
}

void	execute_command(t_command *cmd, t_env **env_list)
{
	int	needs_fork;

	while (cmd)
	{
		needs_fork = (cmd->fd_in >= 0 || cmd->fd_out >= 0 || cmd->pipe_in
				|| cmd->pipe_out);
		if (cmd->path)
		{
			fork_and_execve(cmd, env_list);
		}
		else if (cmd->is_builtin)
		{
			if (needs_fork)
				fork_and_run_builtin(cmd, env_list);
			else
				run_builtin_in_parent(cmd, env_list);
		}
		cmd = cmd->next;
	}
}
