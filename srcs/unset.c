/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:30:57 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:31:00 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_name(char *name)
{
    int i;

    if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
        return (0);
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

/**
* Removes a variable from the environment list by name.
 * name Is the name of the variable to delete.
 * env Pointer to the environment list.
 */
static void remove_var(char *name, t_env **env)
{
    t_env *tmp;
    t_env *prev;

    tmp = *env;
    prev = NULL;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            if (prev)
                prev->next = tmp->next;
            else
                *env = tmp->next;
            free(tmp->name);
            free(tmp->value);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

/**
* The built-in unset command for deleting environment variables.
 * args Array of arguments (args[0] is "unset", args[1] is the first argument).
* env is a pointer to the environment list.
 * ret 0 on success, 1 on error.
 */
int ft_unset(char **args, t_env **env)
{
    int     i;
    int     status;

    status = 0;
    if (!args[1])
    {
        exit_static_status(0);
        return (0);
    }
    i = 1;
    while (args[i])
    {
        if (!is_valid_name(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
        }
        else
            remove_var(args[i], env);
        i++;
    }
    exit_static_status(status);
    return (status);
}

/*
* Tests to verify the operation of ft_unset:
*
* # 1. Deleting an existing variable
* minishell> export TEST=hello
 * minishell> unset TEST
 * minishell> env
 * # Expected output: TEST is missing from the list
*
* # 2. Attempt to delete a non-existent variable
* minishell > unset ABRACADABRA
* minishell> env
 * # Expected output: the list does not change
*
* # 3. Incorrect variable name
* minishell> unset 123invalid
 * # Expected output: minishell: unset: `123invalid': not a valid identifier
 * minishell > echo $?
* # Expected output: 1
 *
* # 4. Deleting multiple variables
 * minishell> export A=1 B=2 C=3
 * minishell> unset A C
 * minishell> env
 * # Expected output: A and C are missing, B=2 is present
*
* # 5. Deleting without arguments
 * minishell> unset
 * minishell > echo $?
* # Expected output: 0
 */
