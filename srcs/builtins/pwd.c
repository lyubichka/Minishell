/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:26:32 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:30:35 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h> 

/**
* Displays the current working directory.
* env is a pointer to the environment list for updating the exit status.
 * ret 0 on success, 1 on error receiving the directory.
 */
int ft_pwd(t_env **env)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        ft_putstr_fd("pwd: error retrieving current directory\n", 2);
        set_exit_status(env, 1);
        return (1);
    }
    ft_putstr_fd(cwd, 1);
    ft_putchar_fd('\n', 1);
    set_exit_status(env, 0);
    return (0);
}

/*
* Tests to verify the operation of ft_pwd:
 *
* # 1. Checking the output of the current directory
 * minishell> pwd
 * # Expected output: /home/user/current/path\n
 * minishell > echo $?
* # Expected output: 0
*
* # 2. Error receiving the catalog
 * minishell> cd /tmp/test && rm -rf /tmp/test && pwd
 * # Expected output: pwd: error retrieving current directory
 * minishell > echo $?
* # Expected output: 1
 *
* # 3. Checking the long path
 * minishell> cd /very/long/path/with/lots/of/subdirs
 * minishell> pwd
 * # Expected output: /very/long/path/with/lots/of/subdirs\n
 * minishell> echo $?
 * # Expected output: 0
*
* # 4. Behavior check when stdout is closed
 * minishell> pwd > /dev/full
 * # Expected output: (depends on the system, output errors are not checked)
* minishell > echo $?
* # Expected output: 0
 */