/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:59:17 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 23:11:46 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_input(t_command *cmd, t_shell *shell)
{
	int	devnull;

	if (cmd->fd_in >= 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("dup2 fd_in", 2);
			shell_cleanup(shell, exit_static_status(1), 1);
		}
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	else if (!cmd->prev && cmd->pipe_out)
	{
		devnull = open("/dev/null", O_RDONLY);
		if (devnull == -1)
			shell_cleanup(shell, exit_static_status(1), 1);
		if (dup2(devnull, STDIN_FILENO) == -1)
		{
			perror("dup2 /dev/null");
			close(devnull);
			shell_cleanup(shell, exit_static_status(1), 1);
		}
		close(devnull);
	}
}

static void	setup_output(t_command *cmd, t_shell *shell)
{
	if (cmd->fd_out >= 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("dup2 fd_out", 2);
			shell_cleanup(shell, exit_static_status(1), 1);
		}
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

void	run_builtin(t_command *cmd, t_env **env_list, t_shell *shell_info)

{
	setup_input(cmd, shell_info);
	setup_output(cmd, shell_info);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		ft_echo(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		ft_cd(cmd->argv, env_list, shell_info);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		ft_pwd(env_list);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		ft_env(env_list);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		ft_export(cmd->argv, env_list, shell_info);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		ft_unset(cmd->argv, env_list, shell_info);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		ft_exit(cmd->argv, shell_info);
	else
		ft_putstr_fd("minishell: unknown builtin\n", 2);
}

void	run_external_command(t_command *cmd, t_env **env_list, t_shell *shell)
{
	char	**env_array;

	env_array = env_list_to_array(*env_list);
	setup_input(cmd, shell);
	setup_output(cmd, shell);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->path, cmd->argv, env_array);
	free_split(env_array);
	shell_cleanup(shell, exit_static_status(127), 1);
}
