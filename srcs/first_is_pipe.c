/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_is_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:32:30 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/09 20:50:01 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_or_last_is_pipe(t_token *tokens)
{
	if (tokens->type == 'p')
		return (-1);
	else
	{
		while (tokens->next)
			tokens = tokens->next;
		if (tokens->type == 'p')
			return (-1);
	}
	return (1);
}
