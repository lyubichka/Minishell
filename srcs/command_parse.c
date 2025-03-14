/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:12:48 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/14 22:25:10 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char *error_token, t_env **env_list)
{
	ft_putstr_fd("syntax error near unexpected token: '",2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd(" ' \n", 2);
	update_exit_status(2, env_list);
	return (-1);
}

int	add_to_argv(t_token *token, t_command *command)
{
	cd
}

int	command_parse(t_command *command, t_token **tokens, t_env **env_list)
{
	t_token	*tmp;
	t_token *prev_tmp;
	int		tokens_processed;
	int		status;
	
	tokens_processed = 0;
	status = 0;
	tmp = *tokens;
	prev_tmp = tmp;
	while (tmp)
	{
		var_expansion(tmp, *env_list);
		if (tmp->type != 'w' && (tokens_processed == 0 || prev_tmp->type != 'w'))
			return (syntax_error(tmp->value, env_list));
		else if (tmp->type == 'p')
			return (0);
		else if (tmp->type == 'w')
			status = add_to_argv(tmp, command);
		else if (tmp->type == 'r')
			status = handle_redir(&tmp, &tokens_processed, command, env_list);
		else if (tmp->type == 'h')
			status = handle_heredoc(&tmp, &tokens_processed, command, env_list);
		if (status == -1)
			return (syntax_error(tmp->value, env_list));
		prev_tmp = tmp;
		tmp = tmp->next;
		tokens_processed++;

		//first check for errors on files, in the order that they are given, but do not exit the line. 
		//for example if i have ls -l < fdd | ls  < output, the second pipe still runs although the first put up an error		
		//if all files are ok, only then we check for the command themselves, same as above with the pipes
		//an error of a command execution it should trigger an exit, only publish a command not found for that pipe
	}
	return (1);
}
