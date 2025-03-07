/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:31:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/07 18:31:22 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *lst_create_envp(char *env_name, char	*env_value)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		return(NULL);
	new_elem->name = env_name;
	new_elem->next = NULL;
	new_elem->value = env_value;
	return(new_elem);
}

t_token *lst_token_create(char type, char *value, int quote)
{
	t_token		*new_elem;

	new_elem = (t_token *)malloc(sizeof(t_token));
	if(!new_elem)
		return (NULL);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->quote = quote;
	new_elem->next = NULL;
}