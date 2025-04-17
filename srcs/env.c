/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:18:34 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/17 23:09:17 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(t_env *env)
{
	ft_putstr_fd(env->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(env->value, 1);
	ft_putchar_fd('\n', 1);
}

int	ft_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->value)
			print_env_var(tmp);
		tmp = tmp->next;
	}
	exit_static_status(0);
	return (0);
}
