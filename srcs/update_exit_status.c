/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:19:11 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/11 22:02:18 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	update_exit_status(int status, t_env **env_list)
// {
// 	t_env	*tmp;
// 	char	*status_str;

// 	tmp = *env_list;
// 	while (tmp)
// 	{
// 		if (ft_strlen(tmp->name) == 1 && ft_strncmp(tmp->name, "?", 2))
// 			break;
// 		tmp = tmp->next;
// 	}
// 	if (tmp)
// 	{
// 		free(tmp->value);
// 		status_str = ft_itoa(status);
// 		tmp->value = ft_strdup(status_str);
// 	}
// }

int	exit_static_status(int set_status)
{
	static int	exit_status;

	if (set_status != -1)
		exit_status = set_status;
	return (exit_status);
}