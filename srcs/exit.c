/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:24:18 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/21 19:49:55 by veronikalub      ###   ########.fr       */
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
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
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
void	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;
	// t_shell *shell = get_shell_info(NULL);

	if (!args || !args[1])
	{
		ft_putstr_fd("exit\n", 1);
		shell_cleanup(shell, exit_static_status(0), 1);
	}
	if (!is_numeric_arg(args[1]))
	{
		ft_putstr_fd("exit\nminishell: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell_cleanup(shell, exit_static_status(2), 1);
	}
	if (args[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit_static_status(1);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	exit_code = ft_atoi(args[1]);
	exit_code = correct_exit_status(exit_code);
	shell_cleanup(shell, exit_static_status(exit_code), 1);
}
