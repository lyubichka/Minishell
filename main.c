/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:37:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/02/24 20:04:46 by saherrer         ###   ########.fr       */
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
	init_signal(); //add a function to kill this process if SHLVL is above limit (200?) before I allocate memory
	envp_to_list(envp, env_list);
	shlvl_increase(env_list);
	return(0);
}

int main(char **av, int ac, char **envp)
{
	t_env	*env_list;
	char	*new_line;
	
	if (boot_shell(ac, envp, &env_list) == 1)
		return (0);
	while (1)
	{
		new_line = readline("minishell>");
		if(!new_line)
		 
	}
}