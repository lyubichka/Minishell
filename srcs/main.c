/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:37:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/04 20:22:58 by saherrer         ###   ########.fr       */
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
	int		status;
	
	if (boot_shell(ac, envp, &env_list) == 1)
		return (0);
	while (1)
	{
		new_line = readline("minishell>");
		if(!new_line)
		{
			ft_putstr_fd("minishell: error: readline failed\n", 2);
			break; //clean exit here? or break and at the end?
		}
		if(*new_line)
		{
			add_history(new_line);
			parse_exec_line(&env_list, new_line); //we can execute from here as well
		}
		free(new_line);
		//break in case of signal and update status
	}
	//clear env list
	return(status);
}