/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:18:34 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:18:36 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Outputs one environment variable in the name=value format.
 * env Pointer to an environment list node.
 */
static void print_env_var(t_env *env)
{
    ft_putstr_fd(env->name, 1);
    ft_putchar_fd('=', 1);
    ft_putstr_fd(env->value, 1);
    ft_putchar_fd('\n', 1);
}

/**
* The built-in env command for displaying environment variables.
 * env Pointer to the environment list.
 * ret is always 0, as output errors are not checked.
 */
int ft_env(t_env **env)
{
    t_env *tmp;

    tmp = *env;
    while (tmp)
    {
        if (tmp->value)
            print_env_var(tmp);
        tmp = tmp->next;
    }
    exit_static_status(0);
    return (0);
}

/*
* Tests to verify the operation of ft_env:
 *
 * # 1. Output of all environment variables
 * minishell> env
 * # Expected output: a list of all variables with values, for example:
* # PATH=/bin:/usr/bin
* # HOME=/home/user
 * # ...
* minishell > echo $?
* # Expected output: 0
*
* # 2. Check for empty environment
 * minishell> unset PATH
 * minishell> unset HOME
 * minishell> env
 * # Expected output: (nothing if there are no variables with values)
* minishell > echo $?
* # Expected output: 0
*
* # 3. Output error (e.g. closed stdout)
 * minishell> env > /dev/full
 * # Expected output: minishell: env: write error
 * minishell > echo $?
* # Expected output: 1
 *
* # 4. Variables without values
 * minishell> export VAR
 * minishell> env
 * # Expected output: VAR is not output because value == NULL
* minishell> echo $?
* # Expected output: 0
 */
