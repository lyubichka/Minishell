/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:15:41 by saherrer          #+#    #+#             */
/*   Updated: 2025/02/23 21:48:57 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_add_front(t_env *new, t_env **lst)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void lst_add_back(t_env *new, t_env **lst)
{
	t_env *tmp;
	
	if (!new || !lst)	
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}