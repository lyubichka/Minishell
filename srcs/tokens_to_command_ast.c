/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_command_ast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:18:20 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/04 17:34:18 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_command(t_command **commands)
{
	(*commands) = (t_command *)malloc(sizeof(t_command));
	(*commands)->fd_in = 0;
	(*commands)->fd_out = 1;
	(*commands)->is_pipe = 0;
	(*commands)->is_builtin = 0;
	(*commands)->is_redir_error = 0;
	(*commands)->argv = NULL;
	(*commands)->path = NULL;
	(*commands)->next = NULL;	
}

int	tokens_to_command_ast(t_command **commands, t_token **tokens, t_env **env_list)
{
	t_token		*tmp_token;
	t_command	*current_cmd;
	t_command	*prior_cmd;
	
	tmp_token = *tokens;
	current_cmd = NULL;
	prior_cmd = NULL;
	while(tmp_token)
	{
		current_cmd = init_command; // init_command(&current_cmd) ?
		if (!*commands)
		{
			*commands = current_cmd;
		}
		if (command_parse(current_cmd, tokens, env_list) == -1)
			return(-1);
		if (prior_cmd && prior_cmd->is_pipe == 1)
			link_commands(prior_cmd, current_cmd, tokens, env_list);
		prior_cmd = current_cmd;
		tmp_token = tmp_token->next;
	}
	
	return (0);
}
