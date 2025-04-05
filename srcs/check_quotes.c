/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:49:57 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/05 20:53:31 by saherrer         ###   ########.fr       */
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
		// if (i > 0 && line[i - 1] == '\\')
		// {
		// 	i++; // no need to treat backlashes anymore
		// 	continue;
		// }
		if (line[i] == '\'' && double_open == 0) // Ignore if inside double quotes
			single_open = !single_open;
		else if (line[i] == '\"' && single_open == 0) // Ignore if inside single quotes
			double_open = !double_open;
		i++;
	}
	if (single_open || double_open)
		ft_putstr_fd("Error: found not closed quote\n", 2);
	return (single_open || double_open);
}