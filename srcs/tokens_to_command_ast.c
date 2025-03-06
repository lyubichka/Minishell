/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_command_ast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:18:20 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/06 19:19:41 by saherrer         ###   ########.fr       */
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
	(*commands)->argv = NULL;
	(*commands)->path = NULL;
	(*commands)->next = NULL;	
}

int	tokens_to_command_ast(t_command **commands, t_token **tokens, t_env **env_list)
{
	t_token	*tmp;
	
	tmp = *tokens;
	init_command(commands);
	while(tmp)
	{
		if(command_parse(commands, tokens, env_list) == -1)
			return(-1);
		tmp = tmp->next;
	}
	return (0);
}