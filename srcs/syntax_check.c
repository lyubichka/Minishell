/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:32:30 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 19:02:05 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *error_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token: '", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("'\n", 2);
	exit_static_status(2);
	return (-1);
}

int	syntax_check(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == 'p' || (!(tokens->next)
			&& (tokens->type == 'r' || tokens->type == 'h')))
		return (syntax_error("newline"));
	while (tokens->next)
	{
		if (tokens->type == 'p')
		{
			if (tokens->next->type == 'p')
				return (syntax_error(tokens->next->value));
		}
		if (tokens->type == 'r' || tokens->type == 'h')
		{
			if (tokens->next->type == 'p' || tokens->next->type == 'r'
				|| tokens->next->type == 'h')
				return (syntax_error(tokens->next->value));
		}
		tokens = tokens->next;
	}
	if (tokens->type == 'p' || tokens->type == 'r' || tokens->type == 'h')
		return (syntax_error(tokens->value));
	return (1);
}

int	line_has_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		else
			i++;
	}
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}
