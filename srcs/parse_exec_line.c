/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:21:00 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/14 23:02:08 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_exec_line(t_env **env_list, char* new_line)
{
	t_token		*tokens;
	t_command	*commands;
	// t_shell		shell_std;
	char		delimiters[10];
	
	tokens = NULL;
	commands = NULL;
	// shell_std.std_in = dup(STDIN_FILENO);
	// shell_std.std_in = dup(STDOUT_FILENO);
	ft_strlcpy(delimiters, "|<>;()& \n",10);
	if (check_quotes(new_line) == 0)
	{
		if (tokenizer(&tokens, new_line, delimiters) == -1)
			return ;
		if (tokens_to_command(&commands, &tokens, env_list) == 0)
		{
			execute_command(commands, env_list);
			 // tokens as well? other memory?
		}
		lst_clear_commands(&commands);
		lst_clear_tokens(&tokens);
	}
	// dup2(shell_std.std_in, STDIN_FILENO);
	// dup2(shell_std.std_out, STDOUT_FILENO);
	// close(shell_std.std_in);
	// close(shell_std.std_out);
}
