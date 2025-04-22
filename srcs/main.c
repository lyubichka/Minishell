/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:37:25 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 20:51:55 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_info(t_shell *shell_info)
{
	shell_info->env_list = NULL;
	shell_info->tokens = NULL;
	shell_info->commands = NULL;
	shell_info->new_line = NULL;
	shell_info->saved_std_in = -1;
	shell_info->saved_std_out = -1;
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
			shell_cleanup(&shell_info, exit_static_status(1), 1);
		}
		shell_info.new_line = new_line;
		if (*new_line != '\0')
			add_history(new_line);
		parse_exec_line(&env_list, new_line, &shell_info);
		init_signal();
	}
	shell_cleanup(&shell_info, exit_static_status(0), 1);
	return (exit_static_status(-1));
}
