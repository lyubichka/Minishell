/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:31:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/18 19:30:40 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lst_create_envp(char *env_name, char *env_value)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	new_elem->name = env_name;
	new_elem->next = NULL;
	new_elem->value = env_value;
	return (new_elem);
}

t_token	*lst_token_create(char type, char *value)
{
	t_token	*new_elem;

	new_elem = (t_token *)malloc(sizeof(t_token));
	if (!new_elem)
		return (NULL);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->id = 0;
	new_elem->next = NULL;
	return (new_elem);
}
