/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:32:50 by veronikalub       #+#    #+#             */
/*   Updated: 2025/03/11 23:36:45 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_exit_status(t_env **env, int status)
{
    char    *status_str;
    t_env   *tmp;
    t_env   *new_node;

    status_str = ft_itoa(status); // Converting a number to a string: 0 → "0", 1 → "1" and so on.
    if (!status_str)
    {
        ft_putstr_fd("minishell: memory error\n", STDERR_FILENO);
        return;
    }
    tmp = *env; // Looking for the variable "?" in the environment list
    while (tmp)
    {
        if (ft_strcmp(tmp->name, "?") == 0)
        {
            free(tmp->value);
            tmp->value = status_str;
            return;
        }
        tmp = tmp->next;
    }
    new_node = lst_create_envp(ft_strdup("?"), status_str); // If the variable is "?" No, we are creating a new one
    if (!new_node)
    {
        free(status_str);
        ft_putstr_fd("minishell: memory error\n", STDERR_FILENO);
        return;
    }
    lst_add_back(new_node, env);
}
