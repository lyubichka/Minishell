/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:25:13 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:25:15 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Checks whether the string is a valid environment variable name.
 * name Is the name of the variable to check.
 * ret 1 if the name is correct, 0 if not.
 */
static int is_valid_name(char *name)
{
    int i;

    if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
        return (0); //The name must begin with a letter or '_'
    i = 1;
    while (name[i] && name[i] != '=') // We check before '=' or the end of the line
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0); // Only letters, numbers, and '_' are allowed.
        i++;
    }
    return (1);
}

/**
* Extracts the name and value from the format string "NAME=VALUE".
 * arg Argument string (for example, "PATH=/bin").
* name Pointer to the string for the name (memory will be allocated).
 * value Pointer to the string for the value (memory will be allocated or NULL).
 */
static void parse_export_arg(char *arg, char **name, char **value)
{
    char *equal_sign;

    equal_sign = ft_strchr(arg, '=');
    if (!equal_sign) // If there is no '=', only the name
    {
        *name = ft_strdup(arg);
        *value = NULL;
    }
    else // If there is a '=', we divide it into a name and a value
    {
        *name = ft_substr(arg, 0, equal_sign - arg);
        *value = ft_strdup(equal_sign + 1);
    }
}

/**
* Updates or adds a variable to the environment list.
 * name Is the name of the variable.
 * value is the value of the variable (it can be NULL).
 * env Pointer to the environment list.
 */
static void update_or_add_var(char *name, char *value, t_env **env)
{
    t_env *tmp;

    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            free(name); // Releasing the duplicate name
            if (value) // If there is a new value, it is updated
            {
                free(tmp->value);
                tmp->value = value;
            }
            else // If there is no value, we leave the old one.
                free(value);
            return;
        }
        tmp = tmp->next;
    }
    // If there is no variable, add a new one.
    tmp = lst_create_envp(name, value);
    if (tmp)
        lst_add_back(tmp, env);
    else
    {
        free(name);
        free(value);
    }
}

/**
* Built-in export command for adding/updating environment variables.
 * args Array of arguments (args[0] is "export", args[1] is the first argument).
* env is a pointer to the environment list.
 * ret 0 on success, 1 on error.
 */
int ft_export(char **args, t_env **env)
{
    int     i;
    char    *name;
    char    *value;
    int     status;

    status = 0;
    if (!args[1]) // If there are no arguments, just exit (bash does not output env)
    {
        exit_static_status(0);
        return (0);
    }
    i = 1;
    while (args[i])
    {
        if (!is_valid_name(args[i]))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
        }
        else
        {
            parse_export_arg(args[i], &name, &value); // We divide it into name and value
            if (!name)
            {
                ft_putstr_fd("minishell: export: memory error\n", 2);
                free(value);
                status = 1;
            }
            else
                update_or_add_var(name, value, env);
        }
        i++;
    }
    exit_static_status(status);
    return (status);
}

/*
* Tests to verify the operation of ft_export:
* 1. Exporting a new variable with a value
 * minishell> export TEST=hello
 * minishell> env
 * # Expected output: TEST=hello in the list
*
* 2. Export without value (add without modification)
* minishell > export NEWVAR
* minishell> env
 * # Expected output: NEWVAR with no value (NULL in value)
*
* 3. Updating an existing variable
* minishell> export PATH=/new/path
 * minishell> env
 * # Expected output: PATH=/new/path
*
* 4. Invalid variable name
 * * minishell> export123=invalid
 * # Expected output: minishell: export: `123=invalid': not a valid identifier
 * minishell > echo $?
* # Expected output: 1
 *
* 5. Multiple arguments
 * minishell> export A=1 B=2 C
 * minishell> env
 * # Expected output: A=1, B=2, C in the list
 */
