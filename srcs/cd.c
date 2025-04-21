/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:17:40 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/21 22:38:28 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_home_case(char *home)
{
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		exit_static_status(1);
		return (NULL);
	}
	return (home);
}

static char	*get_target_dir(char **args, t_env **env)
{
	char	*home;
	char	*oldpwd;

	home = get_env_value("HOME", *env);
	oldpwd = get_env_value("OLDPWD", *env);
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
		return (handle_home_case(home));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		if (!oldpwd)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			exit_static_status(1);
			return (NULL);
		}
		return (oldpwd);
	}
	return (args[1]);
}

static void	update_env_var(char *name, char *value, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				ft_putstr_fd("minishell: cd: memory allocation failed\n", 2);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = lst_create_envp(ft_strdup(name), ft_strdup(value));
	if (tmp)
		lst_add_back(tmp, env);
	else
		ft_putstr_fd("minishell: cd: memory allocation failed\n", 2);
}

static int	prepare_cd(char **args, char *oldpwd, t_env **env)
{
	char	*env_pwd;

	env_pwd = get_env_value("PWD", *env);
	if (!getcwd(oldpwd, PATH_MAX))
	{
		if (env_pwd)
			ft_strlcpy(oldpwd, env_pwd, PATH_MAX);
		else
		{
			ft_putstr_fd("minishell: cd: getcwd error\n", 2);
			exit_static_status(1);
			return (0);
		}
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		exit_static_status(1);
		return (0);
	}
	return (1);
}

int	ft_cd(char **args, t_env **env, t_shell *shell)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*target_dir;

	if (!prepare_cd(args, oldpwd, env))
		return (1);
	target_dir = get_target_dir(args, env);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
		return (handle_cd_error(target_dir));
	update_env_var("OLDPWD", oldpwd, env);
	if (!getcwd(pwd, PATH_MAX))
	{
		ft_putstr_fd("minishell: cd: getcwd error\n", 2);
		return (exit_static_status(1));
	}
	update_env_var("PWD", pwd, env);
	shell->env_list = *env;
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	return (exit_static_status(0));
}
