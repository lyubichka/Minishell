/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:21:00 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/15 19:37:27 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_exec_line(t_env **env_list, char* new_line, t_shell *shell_info)
{
	t_token		*tokens;
	t_command	*commands;
	char		delimiters[10];
	
	tokens = NULL;
	commands = NULL;
	ft_strlcpy(delimiters, "|<>;()& \n",10);
	if (check_quotes(new_line) == 0)
	{
		if (tokenizer(&tokens, new_line, delimiters) == -1)
			return ;
		shell_info->tokens = &tokens;
		if (tokens_to_command(&commands, &tokens, env_list) == 0)
		{
			shell_info->commands = &commands;
			execute_command(commands, env_list);
			 // tokens as well? other memory?
		}
		lst_clear_commands(&commands);
		lst_clear_tokens(&tokens);
	}

}
