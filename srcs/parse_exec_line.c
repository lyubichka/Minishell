/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:21:00 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:35 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell_info(t_shell *set_shell)
{
	static t_shell	*shell;
	
	if (set_shell != NULL)
		shell = set_shell;
	return (shell);
}

void	parse_exec_line(t_env **env_list, char *new_line, t_shell *shell_info)
{
	t_token		*tokens;
	t_command	*commands;
	char		delimiters[10];

	tokens = NULL;
	commands = NULL;
	ft_strlcpy(delimiters, "|<>\t \n", 7);
	if (check_quotes(new_line) == 0)
	{
		if (tokenizer(&tokens, new_line, delimiters) == -1)
			return ;
		shell_info->tokens = &tokens;
		if (tokens_to_command(&commands, &tokens, env_list) == 0)
		{
			shell_info->commands = &commands;
			// get_shell_info(shell_info);
			execute_command(commands, env_list, shell_info);
			// tokens as well? other memory?
		}
		shell_cleanup(shell_info, exit_static_status(-1), 0);
		// lst_clear_commands(&commands);
		// lst_clear_tokens(&tokens);
	}
}
