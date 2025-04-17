/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 22:46:56 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, t_env *env)
{
	while (env && name)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	envp_to_list(char **envp, t_env **env_list)
{
	int		i;
	char	*env_name;
	char	*env_value;
	int		eq_pos;
	t_env	*node;

	i = 0;	
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			eq_pos = ft_strchr(envp[i], '=') - envp[i];
			env_name = ft_substr(envp[i], 0, eq_pos);
			env_value = ft_substr(envp[i], eq_pos + 1, ft_strlen(envp[i]) - eq_pos - 1);
			node = lst_create_envp(env_name, env_value);
			lst_add_back(node, env_list);
		}
		i++;
	}
	return (0);
}
