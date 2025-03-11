/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:04:46 by veronikalub       #+#    #+#             */
/*   Updated: 2025/03/12 02:04:50 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_env *env)
{
    t_env *current;

    current = env;
    while (current != NULL)
    {
        if (current->value != NULL)
        {
            ft_putstr_fd(current->name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(current->value, 1);
            ft_putstr_fd("\n", 1);
        }
        current = current->next;
    }
    set_exit_status(env, 0);
    return (0);
}

// # 1. Output of all variables
// minishell > env
// PATH=/usr/bin:/bin
// USER=nika
// ...

// #2. Write error (e.g. closed STDOUT)
// minishell> env > /dev/full
// minishell> echo $?
// 1

// #3. Variables without a value are not output
// minishell> export EMPTY=
// minishell> env
// # EMPTY will not be displayed
