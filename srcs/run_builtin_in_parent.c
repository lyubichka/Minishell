/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_in_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:33:22 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 20:57:55 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtin_in_parent(t_command *cmd, t_env **env_list,\
								t_shell *shell)
{
	shell->saved_std_in = dup(STDIN_FILENO);
	if (shell->saved_std_in == -1)
	{
		ft_putstr_fd("dup shell->saved_std_in", 2);
		shell_cleanup(shell, exit_static_status(1), 1) ;
	}
	shell->saved_std_out = dup(STDOUT_FILENO);
	if (shell->saved_std_out == -1)
	{
		perror("dup shell->saved_std_out");
		shell_cleanup(shell, exit_static_status(1), 1);
	}
	run_builtin(cmd, env_list, shell);
	if (dup2(shell->saved_std_in, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2 shell->saved_std_in", 2);
		shell_cleanup(shell, exit_static_status(1), 1);
	}
	if (dup2(shell->saved_std_out, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 shell->saved_std_out", 2);
		shell_cleanup(shell, exit_static_status(1), 1);
	}
	if (shell->saved_std_in != -1)
		close(shell->saved_std_in);
	shell->saved_std_in = -1;
	if (shell->saved_std_out != -1)
		close(shell->saved_std_out);
	shell->saved_std_out = -1;
}
