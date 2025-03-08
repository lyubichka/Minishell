/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:19:11 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/08 21:34:58 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(int status, t_env **env_list)
{
	t_env	*tmp;
	char	*status_char;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strlen(tmp->name) == 1 && ft_strncmp(tmp->name, "?", 2))
			break;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->value);
		status_char = ft_itoa(status);
		tmp->value = ft_strdup(status_char);
	}
}