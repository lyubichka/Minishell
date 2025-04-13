/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:03:06 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/03 20:06:24 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_clear_tokens(t_token **tokens)
{
	t_token *tmp1;
	t_token *tmp2;

	tmp1 = *tokens;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1->value);
		free(tmp1);
		tmp1 = tmp2;
	}
	*tokens = NULL;
}

void	lst_clear_env(t_env **env)
{
	t_env *tmp1;
	t_env *tmp2;

	tmp1 = *env;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1->name);
		free(tmp1->value);
		free(tmp1);
		tmp1 = tmp2;
	}
	*env = NULL;
}

void lst_clear_commands(t_command **commands)
{
	
}