/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_command_ast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:18:20 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/04 20:43:54 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_to_command_ast(t_command **commands, t_token **tokens, t_env **env_list)
{
	t_token	*tmp;
	
	tmp = *tokens;
	init_command(commands);
	while(tmp)
	{
		if(parse_command(commands, tokens, env_list) == -1)
			return(-1);
		tmp = tmp->next;
	}
	return (0);
}