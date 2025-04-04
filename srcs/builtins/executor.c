/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:22:43 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:22:45 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_command *command, t_env **env_list)
{
    if (command->is_builtin)
    {
        if (ft_strcmp(command->argv[0], "cd") == 0)
            ft_cd(command->argv, env_list);
        else if (ft_strcmp(command->argv[0], "echo") == 0)
            ft_echo(command->argv);
        else if (ft_strcmp(command->argv[0], "env") == 0)
            ft_env(*env_list);
        else if (ft_strcmp(command->argv[0], "pwd") == 0)
            ft_pwd(env_list);
        else if (ft_strcmp(command->argv[0], "export") == 0)
            ft_export(command->argv, env_list);
        else if (ft_strcmp(command->argv[0], "unset") == 0)
            ft_unset(command->argv, env_list);
        else if (ft_strcmp(command->argv[0], "exit") == 0)
            ft_exit(command->argv, env_list);
    }
    else
    {
        // Logic for executing external commands (fork, execve, etc.)
    }
}