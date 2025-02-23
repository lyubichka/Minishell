/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:37:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/02/23 21:09:41 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int boot_shell(int ac, char **envp, t_env **env_list)
{
	if (ac > 1)
	{
		ft_putstr_fd("No arguments should be entered\n", 2);
		return (1);
	}
	init_signal();
	envp_to_list(envp, env_list);
	
	
}

int main(char **av, int ac, char **envp)
{
	t_env	*env_list;
	
	if (boot_shell(ac, envp, &env_list) == 1)
		return (0);
	while (1)
	{
		1;
	}
}