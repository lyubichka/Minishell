/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/02/23 22:23:49 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int envp_to_list(char **envp, char **env_list)
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
}