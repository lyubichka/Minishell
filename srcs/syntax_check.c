/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:32:30 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/11 20:46:41 by saherrer         ###   ########.fr       */
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

int	syntax_error(char *error_token)
{
	ft_putstr_fd("syntax error near unexpected token: '",2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd(" ' \n", 2);
	exit_static_status(2);
	return (-1);
}

int	syntax_check(t_token *tokens)
{
	if (tokens->type == 'p')
		return (-1);
	while (tokens->next)
	{
		if (tokens->type == 'p')
		{
			if (tokens->next->type == 'p')
				return (syntax_error(tokens->next));
		}
		if (tokens->type == 'r' || tokens->type == 'h')
		{
			if (tokens->next->type == 'p' || tokens->next->type == 'r' || tokens->next->type == 'h')
				return (syntax_error(tokens->next));
		}
		tokens = tokens->next;
	}
	if (tokens->type == 'p' || tokens->next->type == 'r' || tokens->next->type == 'h')
		return (syntax_error(tokens));
	return (1);
}