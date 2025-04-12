/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:48 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/09 22:27:34 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **array)
{
	char	**current;
	int		i;

	i = 0;
	current = array;
	if (array)
	{
		while (current[i])
		{
			free(current[i]);
			current[i] = NULL;
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	free_command(t_command *cmd)
{
    if (cmd)
    {
        if (cmd->argv)
            free_split(cmd->argv);
        if (cmd->path)
            free(cmd->path);
        free(cmd);
    }
}

void	lst_clear_commands(t_command **commands)
{
    t_command *tmp;
    t_command *next;

    tmp = *commands;
    while (tmp)
    {
        next = tmp->next;
        free_command(tmp);
        tmp = next;
    }
    *commands = NULL;
}

void	lst_clear_env(t_env **env_list)
{
    t_env *tmp;
    t_env *next;

    tmp = *env_list;
    while (tmp)
    {
        next = tmp->next;
        if (tmp->name)
            free(tmp->name);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
        tmp = next;
    }
    *env_list = NULL;
}
