/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:25:13 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/21 22:35:17 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		*name = ft_strdup(arg);
		*value = NULL;
	}
	else
	{
		*name = ft_substr(arg, 0, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
}

static void	update_or_add_var(char *name, char *value, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
		{
			free(name);
			if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			return ;
		}
		tmp = tmp->next;
	}
	tmp = lst_create_envp(name, value);
	if (!tmp)
	{
		free(name);
		free(value);
	}
	lst_add_back(tmp, env);
}

static int	handle_valid_export(char *arg, t_env **env)
{
	char	*name;
	char	*value;

	parse_export_arg(arg, &name, &value);
	if (!name)
	{
		ft_putstr_fd("minishell: export: memory error\n", 2);
		free(value);
		return (1);
	}
	update_or_add_var(name, value, env);
	return (0);
}

int	ft_export(char **args, t_env **env, t_shell *shell)
{
	int	i;
	int	status;

	status = 0;
	if (!args[0] || !args[1])
		return (exit_static_status(0));
	i = 1;
	while (args[i])
	{
		if (!is_valid_name(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			status |= handle_valid_export(args[i], env);
		i++;
	}
	shell->env_list = *env;
	return (exit_static_status(status));
}
