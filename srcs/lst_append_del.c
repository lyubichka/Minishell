/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_append_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:01:15 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/03 19:29:27 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_token_append(t_token *new_elem, t_token *tmp1, t_token *tmp2)
{
	tmp1->next = new_elem;
	new_elem->next = tmp2;
}

void	lst_token_del(t_token *prev, t_token *curr, t_token *forw)
{
	if (prev)
		prev->next = forw;
	free(curr->value);
	free(curr);
}
