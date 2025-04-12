/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:17:40 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:20:41 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/**
* Defines the target directory for the cd command.
 * args Array of arguments (args[1] is the path, if specified).
 * env Pointer to the environment list.
 * ret A pointer to the string with the target directory, or NULL in case of an error.
 */
static char *get_target_dir(char **args, t_env **env)
{
    char    *home;
    char    *oldpwd;
    
    
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        char *home = get_env_value("HOME", *env);
        if (!home)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            exit_static_status(1);
            return (NULL);
        }
        return (home);
    }
    if (ft_strcmp(args[1], "-") == 0)
    {
        char *oldpwd = get_env_value("OLDPWD", *env);
        if (!oldpwd)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            exit_static_status(1);
            return (NULL);
        }
        return (oldpwd);
    }
    return (args[1]);
}

/**
* Gets the value of the environment variable by name.
 * name Is the name of the variable.
 * env Environment list.
 * ret A pointer to a value or NULL if the variable is not found.
 */
static char *get_env_value(char *name, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

/**
* Updates or adds an environment variable.
 * name Is the name of the variable.
 * value is the new value of the variable.
 * env Pointer to the environment list.
 */
static void update_env_var(char *name, char *value, t_env **env)
{
    t_env *tmp;
    
    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            if (!tmp->value)
                ft_putstr_fd("minishell: cd: memory allocation failed\n", 2);
            return;
        }
        tmp = tmp->next;
    }
    tmp = lst_create_envp(ft_strdup(name), ft_strdup(value));
    if (tmp)
        lst_add_back(tmp, env);
    else
        ft_putstr_fd("minishell: cd: memory allocation failed\n", 2);
}

static int handle_cd_error(char *target_dir, t_env **env)
{
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(target_dir, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    exit_static_status(1);
    return (1);
}

/**
* Executes the cd command to change the current directory.
 * args Array of arguments (args[0] — "cd", args[1] — path).
 * env Pointer to the environment list.
 * ret 0 on success, 1 on error.
 */
int ft_cd(char **args, t_env **env)
{
    char oldpwd[PATH_MAX];
    char pwd[PATH_MAX];
    char *target_dir;

    if (!getcwd(oldpwd, PATH_MAX)) // Saving the current directory in OLDPWD
        return (ft_putstr_fd("cd: getcwd error\n", 2), set_exit_status(env, 1), 1);
    if (args[1] && args[2])
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        exit_static_status(1);
        return (1);
    }
    target_dir = get_target_dir(args, env); // Defining the target directory
    if (!target_dir)
        return (1);
    if (chdir(target_dir) != 0)
        return (handle_cd_error(target_dir, env));
    update_env_var("OLDPWD", oldpwd, env);
    if (!getcwd(pwd, PATH_MAX)) // We get a new current catalog and update the PWD
    {
        ft_putstr_fd("cd: getcwd error\n", 2);
        exit_static_status(1);
        return (1);
    }
    update_env_var("PWD", pwd, env);
    if (args[1] && ft_strcmp(args[1], "-") == 0) // We output a new path when using "-"
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
    }
    exit_static_status(0);
    return (0);
}

/*
* Tests to verify ft_cd operation:
*
* # 1. Go to the home directory (without arguments)
* minishell > cd
* minishell> pwd
 * # Expected output: /home/user (HOME value)
*
* # 2. Move to the previous directory
 * minishell> cd /tmp
 * minishell> cd -
 * # Expected output: /home/user (previous PWD)
* minishell > echo $?
* # Expected output: 0
*
* # 3. Move to a non-existent directory
 * minishell> cd /nonexistent
 * # Expected output: cd: /nonexistent: No such file or directory
 * minishell > echo $?
* # Expected output: 1
 *
* # 4. Too many arguments
 * minishell> cd dir1 dir2
 * # Expected output: cd: too many arguments
 * minishell > echo $?
* # Expected output: 1
 *
* # 5. Navigating to a directory without access rights
 * minishell> cd /root
 * # Expected output: cd: /root: Permission denied
 * minishell > echo $?
* # Expected output: 1
 */
