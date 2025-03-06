/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_increase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:15:48 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/06 18:37:07 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lvl_change(int *lvl, char *value)
{
	*lvl = ft_atoi(value);
	if (*lvl <= 0)
		*lvl = 1;
	else
		(*lvl)++;
}

void	shlvl_increase(t_env **env_list)
{
	t_env	*tmp;
	int		lvl;
	t_env	*node;

	tmp = *env_list;
	lvl = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "SHLVL", ft_strlen(tmp->name)) == 0)
		{
			lvl_change(&lvl, tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		node = lst_create_envp(ft_strdup("SHLVL"), ft_strdup("1"));
		lst_add_back(node, env_list);
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup(ft_itoa(lvl));
	}
}
