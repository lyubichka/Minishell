/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:21:00 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/08 21:36:22 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_exec_line(t_env **env_list, char* new_line)
{
	t_token		*tokens;
	t_command	*commands;
	char		delimiters[10];
	
	ft_strlcpy(delimiters, "|<>;()& \n",10);
	if (check_quotes(new_line) == 0)
	{
		if (tokenizer(&tokens, new_line, delimiters, env_list) == -1)
			return ;
		if (tokens_to_command_ast(&commands, &tokens, env_list) == 1)
			//execute
		//lst_clear_commands(&commands);
		lst_clear_tokens(&tokens);
	}
}