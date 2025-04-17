/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:18:14 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/17 23:08:25 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int ft_echo(char **args)
{
	int n_flag;
	int i;

	n_flag = 0;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	if (args[i])
	{
		print_args(args, i);
		ft_putchar_fd('\n', 1);
	}
	else if (!n_flag)
		ft_putchar_fd('\n', 1);
	exit_static_status(0);
	return (0);
}
