/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:12:48 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/09 21:11:36 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_parse(t_command **commands, t_token **tokens, t_env **env_list)
{
	t_token	*tmp;
	
	tmp = *tokens;
	if (tmp->type == 'p')
		return (0);
	else 
	
}