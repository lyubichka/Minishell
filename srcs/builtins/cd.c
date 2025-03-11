/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:28:20 by veronikalub       #+#    #+#             */
/*   Updated: 2025/03/11 23:36:54 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_target_dir(char **args, t_env **env)
{
    char *target_dir;

    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        target_dir = get_env_value("HOME", *env);
        if (!target_dir)
            handle_error(NULL, "HOME not set", env);
        return (target_dir);
    }
    if (ft_strcmp(args[1], "-") == 0)
    {
        target_dir = get_env_value("OLDPWD", *env);
        if (!target_dir)
            handle_error(NULL, "OLDPWD not set", env);
        return (target_dir);
    }
    return (args[1]);
}

static char *get_env_value(char *name, t_env *env)
{
    // Searching for the value of a variable in the list env
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

static void	update_env_var(char *name, char *value, t_env **env)
{
    t_env	*tmp;
    t_env   *new_node;
    
    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }
    new_node = lst_create_envp(ft_strdup(name), ft_strdup(value));
    lst_add_back(new_node, env);
}

static int	handle_error(char *path, char *error_msg, t_env **env)
{
    ft_putstr_fd("cd: ", 2);
    if (path)
    {
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putstr_fd(error_msg, 2);
    ft_putstr_fd("\n", 2);
    set_exit_status(env, 1);
    return (1);
}

int	ft_cd(char **args, t_env **env)
{
    char    oldpwd[1024];
    char    pwd[1024];
    char    *target_dir = NULL;
    int     free_flag = 0;

    if (!getcwd(oldpwd, 1024))
        return (handle_error(NULL, "getcwd error", env));
    target_dir = get_target_dir(args, env);
    if (!target_dir)
        return (1);
    if (args[1] && args[2])
        return (handle_error(NULL, "too many arguments", env));
    if (chdir(target_dir) != 0) // Attempt to change the directory
        return (handle_error(target_dir, strerror(errno), env));
    update_env_var("OLDPWD", oldpwd, env); // Updating the environment
    if (!getcwd(pwd, 1024))
        return (handle_error(NULL, "getcwd error", env));
    update_env_var("PWD", pwd, env);
    if (args[1] && ft_strcmp(args[1], "-") == 0) // PWD output for cd -
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
    }
    if (free_flag)
        free(target_dir);
    set_exit_status(env, 0);
    return (0);
}

// tests.
// 1: No arguments (must use HOME)
// > cd

// 2: Return to the previous directory
// > cd -
// > cd /tmp
// > cd -

// 3: A non-existent path
// > cd /non-existent path

// 4: Too many arguments
// > cd dir1 dir2

// 5: Special Characters
// > cd ~
// > cd ..
