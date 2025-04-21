/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:37:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/21 21:53:22 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_info(t_shell *shell_info)
{
	shell_info->env_list = NULL;
	shell_info->tokens = NULL;
	shell_info->commands = NULL;
}

static int	boot_shell(int ac, char **envp, t_env **env_list,
		t_shell *shell_info)
{
	if (ac > 1)
	{
		ft_putstr_fd("No arguments should be entered\n", 2);
		exit (127);
	}
	init_signal();
	envp_to_list(envp, env_list);
	shlvl_increase(env_list);
	shell_info->env_list = *env_list;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	char	*new_line;
	t_shell	shell_info;

	(void)av;
	env_list = NULL;
	init_shell_info(&shell_info);
	if (boot_shell(ac, envp, &env_list, &shell_info) == 1)
		return (0);
	while (1)
	{
		new_line = readline("minishell> ");
		if (!new_line)
		{
			// lst_clear_env(&env_list);
			// rl_clear_history();
			// ft_exit(NULL);
			shell_cleanup(&shell_info, exit_static_status(1), 1);
		}
		// if (ft_strncmp(new_line, "", ft_strlen(new_line)) != 0)
		// 	add_history(new_line);
		if (*new_line != '\0')
			add_history(new_line);
		parse_exec_line(&env_list, new_line, &shell_info);
		// free(new_line);
		init_signal();
		// break in case of signal and update status
	}
	// lst_clear_env(&env_list);
	// rl_clear_history();
	shell_cleanup(&shell_info, exit_static_status(0), 1);
	return (exit_static_status(-1));
}
