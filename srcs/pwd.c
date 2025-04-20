/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:26:32 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/20 17:44:32 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env_list)
{
	char	cwd[PATH_MAX];
	char	*env_pwd;

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		exit_static_status(0);
		return (0);
	}
	env_pwd = get_env_value("PWD", *env_list);
	if (env_pwd)
	{
		ft_putstr_fd(env_pwd, 1);
		ft_putchar_fd('\n', 1);
		exit_static_status(0);
		return (0);
	}
	ft_putstr_fd("pwd: error retrieving current directory\n", 2);
	exit_static_status(1);
	return (1);
}
