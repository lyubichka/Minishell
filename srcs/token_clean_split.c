/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clean_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:22:15 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 20:12:40 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_append(t_token *tmp1, t_token *tmp2)
{
	char	**tmp_array;
	int		i;
	t_token	*new_elem;

	i = 0;
	tmp_array = ft_split(tmp1->value, ' ');
	if (tmp_array && tmp_array[0])
	{
		while (tmp_array[i])
		{
			new_elem = lst_token_create('o', ft_strdup(tmp_array[i]));
			lst_token_append(new_elem, tmp1, tmp2);
			tmp1 = new_elem;
			i++;
		}
	}
	if (tmp_array)
		free_split(tmp_array);
}

void	token_split(t_token **tokens)
{
	t_token	*tmp1;
	t_token	*tmp2;

	if (!tokens || !*tokens)
		return ;
	tmp1 = *tokens;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (tmp1->type == 'o' && ft_strchr(tmp1->value, ' ') != NULL)
		{
			tmp1->type = 'd';
			token_append(tmp1, tmp2);
		}
		tmp1 = tmp2;
	}
}

static void	delete_token_if_discarded(t_token **tokens, t_token **curr,
										t_token **prev, t_token *forw)
{
	if ((*curr)->type == 'd')
	{
		if (*prev)
			(*prev)->next = forw;
		else
			*tokens = forw;
		free((*curr)->value);
		(*curr)->value = NULL;
		free(*curr);
		*curr = NULL;
	}
	else
	{
		*prev = *curr;
	}
}

void	token_cleanup(t_token **tokens)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*forw;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		forw = curr->next;
		delete_token_if_discarded(tokens, &curr, &prev, forw);
		curr = forw;
	}
}

void	token_index(t_token *tokens)
{
	int	id;

	id = 0;
	while (tokens)
	{
		tokens->id = id;
		tokens = tokens->next;
		id++;
	}
}
