/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:49:57 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/18 16:55:41 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line)
{
	int	i;
	int	single_open;
	int	double_open;

	i = 0;
	single_open = 0;
	double_open = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && double_open == 0)
			single_open = !single_open;
		else if (line[i] == '\"' && single_open == 0)
			double_open = !double_open;
		i++;
	}
	if (single_open || double_open)
	{
		ft_putstr_fd("minishell: found not closed quote\n", 2);
		exit_static_status(1);
	}
	return (single_open || double_open);
}
