/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:48 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 20:53:45 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	shell_cleanup(t_shell *shell, int exit_code, int env_flag)
{
	if (shell)
	{
		if (shell->env_list && env_flag == 1)
			lst_clear_env(&(shell->env_list));
		if (shell->tokens)
			lst_clear_tokens(&(shell->tokens));
		if (shell->commands)
			lst_clear_commands(&(shell->commands));
		if (shell->new_line)
		{
			free(shell->new_line);
			shell->new_line = NULL;
		}
		if (shell->saved_std_in != -1)
		{
			close(shell->saved_std_in);
			shell->saved_std_in = -1;
		}
		if (shell->saved_std_out != -1)
		{
			close(shell->saved_std_out);
			shell->saved_std_out = -1;
		}
	}
	if (env_flag == 1)
		rl_clear_history();
	if (env_flag == 1)
		exit(exit_code);
}

