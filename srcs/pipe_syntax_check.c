/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:32:30 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/09 21:54:54 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	first_or_last_is_pipe(t_token *tokens)
// {
// 	if (tokens->type == 'p')
// 		return (-1);
// 	else
// 	{
// 		while (tokens->next)
// 			tokens = tokens->next;
// 		if (tokens->type == 'p')
// 			return (-1);
// 	}
// 	return (1);
// }

int	pipe_syntax_check(t_token *tokens)
{
	if (tokens->type == 'p')
		return (-1);
	while (tokens->next)
	{
		if (tokens->type == 'p')
		{
			if (tokens->next->type == 'p')
				return (syntax_error(tokens), -1);
		}
		tokens = tokens->next;
	}
	if (tokens->type == 'p')
		return (syntax_error(tokens), -1);
	return (1);
}