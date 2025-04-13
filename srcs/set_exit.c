/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:30:46 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:30:48 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_exit_status(t_env **env, int status)
{
    char    *status_str;
    t_env   *tmp;
    t_env   *new_node;

    status_str = ft_itoa(status); // Converting the status to a string: 0 → "0", 1 → "1" and so on.
    if (!status_str)
    {
        ft_putstr_fd("minishell: memory error\n", STDERR_FILENO);
        return;
    }
    tmp = *env; //  Looking for the variable "?" in the environment list
    while (tmp)
    {
        if (ft_strncmp(tmp->name, "?", 2) == 0)
        {
            free(tmp->value); // Releasing the old value
            tmp->value = status_str; // Assign a new value
            return;
        }
        tmp = tmp->next;
    }
    // If "?" not found, creating a new node
    new_node = lst_create_envp(ft_strdup("?"), status_str);
    if (!new_node)
    {
        free(status_str); // Freeing the row if node creation failed
        ft_putstr_fd("minishell: memory error\n", STDERR_FILENO);
        return;
    }
    lst_add_back(new_node, env); // Adding a new node to the end of the list
}
