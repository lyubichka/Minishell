/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:24:18 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/17 23:12:41 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	correct_exit_status(long res)
{
	if (res >= 0 && res <= 255)
		return (res);
	res = res % 256;
	if (res < 0)
		res += 256;
	return (res);
}

static int	is_numeric_arg(char *str)
{
	int i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++; // Skip the sign
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
* Built-in exit command for shell shutdown.
 * args Array of arguments (args[0] — "exit", args[1] — exit code, if any).
* env Pointer to the environment list to update $?.
* ret Does not return a value, terminates the program.
 */
void	ft_exit(char **args)
{
	int exit_code;

	if (!args[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit(exit_static_status(0));
	}
	if (!is_numeric_arg(args[1]))
	{
		ft_putstr_fd("exit\nminishell: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(exit_static_status(2));
	}
	if (args[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit_static_status(1);
		return;
	}
	ft_putstr_fd("exit\n", 1);
	exit_code = ft_atoi(args[1]);
	exit_code = correct_exit_status(exit_code);
	exit(exit_static_status(exit_code));
}
