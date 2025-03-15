/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:44:23 by veronikalub       #+#    #+#             */
/*   Updated: 2025/03/15 23:18:57 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>

int ft_pwd(t_env **env)
{
    char    cwd[1024];
    int     write_status;

    (void)env; // Явное указание на неиспользуемый аргумент

    write_status = 0;
    if (!getcwd(cwd, 1024))
    {
        ft_putstr_fd("minishell: pwd: ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        set_exit_status(env, 1);
        return (1);
    }
    if (ft_putstr_fd(cwd, 1) == -1 ||
        ft_putstr_fd("\n", 1) == -1)
        write_status = 1;
    set_exit_status(env, write_status);
    return (write_status);
}

// # Normal operation
// minishell> pwd
// /home/user/projects/minishell

// # Write error (e.g. closed STDOUT)
// minishell> pwd > /dev/full
// minishell> echo $?
// 1

// # getcwd error (for example, deleting the current directory)
// minishell> cd /tmp && rm -rf /tmp && pwd
// minishell: pwd: No such file or directory