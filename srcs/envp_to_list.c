/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/07 21:14:01 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void exit_status_node(t_env **env_list)
// {
// 	char	*value;
// 	char	*name;
// 	t_env	*new_exit_node;

// 	value = ft_strdup("0");
// 	name = ft_strdup("?");
// 	new_exit_node = lst_create_envp(name, value);
// 	lst_add_front(new_exit_node, env_list);
// }

int envp_to_list(char **envp, t_env **env_list)
{
	int i;
	char *env_name;
	char *env_value;
	int eq_pos;
	t_env *node;

	i = 0;	
	while(envp[i])
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
	// exit_status_node(env_list);
	return (0);
}

// should add the ? here to update it between runs? ---> NO, will handle with a static INT instead.