/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:15:41 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/02 20:55:46 by saherrer         ###   ########.fr       */
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

void token_add_front(t_token *new, t_token **lst) //maybe will not be used
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void token_add_back(t_token *new, t_token **lst)
{
	t_token *tmp;
	
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