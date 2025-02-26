/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:49:57 by saherrer          #+#    #+#             */
/*   Updated: 2025/02/26 21:46:13 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_single(char *line)
// {
// 	int	i;
// 	int	count;
	
// 	i = 0;
// 	count = 0;
// 	while (line[i] != '\0')
// 	{
// 		if(line[i] == '\'')
// 			count++;
// 		i++;
// 	}
// 	if(count % 2 == 0)
// 		return (0);
// 	else
// 	{
// 		ft_putstr_fd("Error: found not closed single quote\n", 2);
// 		return (1);
// 	}
// }

// static int	check_double(char *line)
// {
// 	int	i;
// 	int	count;
	
// 	i = 0;
// 	count = 0;
// 	while (line[i] != '\0')
// 	{
// 		if(line[i] == '\"')
// 			count++;
// 		i++;
// 	}
// 	if(count % 2 == 0)
// 		return (0);
// 	else
// 	{
// 		ft_putstr_fd("Error: found not closed double quote\n", 2);
// 		return (1);
// 	}
// }

// int	check_quotes(char *line)
// {
// 	if (check_single(line) == 1 || check_double(line) == 1)
// 		return (1);
// 	return (0);
// }

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