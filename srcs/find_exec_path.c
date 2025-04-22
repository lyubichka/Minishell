/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:06:49 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 22:22:50 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	path_error_setting(t_command *command, char *cmd_name,
		char **paths, char *last_path)
{
	command->is_redir_error = 1;
	if (!paths || !last_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_static_status(127);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit_static_status(126);
	}
}

static int	handle_direct_path(char *cmd_name, t_command *cmd)
{
	if (cmd_name[0] != '\0' && access(cmd_name, X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd_name);
		return (0);
	}
	else if (cmd_name[0] != '\0' && access(cmd_name, F_OK) == 0)
		path_error_setting(cmd, cmd_name, NULL, "DENIED");
	else
		path_error_setting(cmd, cmd_name, NULL, NULL);
	return (-1);
}

static int	handle_path_not_found(char **paths, char *cmd_name,
		t_command *command, int i)
{
	if (!paths || cmd_name[0] == '\0')
	{
		path_error_setting(command, cmd_name, paths, NULL);
	}
	else
	{
		path_error_setting(command, cmd_name, paths, paths[i]);
		free_split(paths);
	}
	return (-1);
}

static int	search_in_paths(char **paths, char *cmd_name, t_command *cmd)
{
	int		i;
	char	*joined;

	i = 0;
	while (paths && paths[i] && cmd_name[0] != '\0')
	{
		joined = join_path(paths[i], cmd_name);
		if (access(joined, F_OK) == 0)
		{
			if (access(joined, X_OK) == 0)
			{
				free_split(paths);
				cmd->path = joined;
				return (0);
			}
			else
			{
				free(joined);
				break ;
			}
		}
		free(joined);
		i++;
	}
	return (handle_path_not_found(paths, cmd_name, cmd, i));
}

int	find_exec_path(char *cmd_name, t_env *env_list, t_command *cmd)
{
	char	**paths;
	char	*path_env;

	if (!cmd_name)
		return (-1);
	if (is_builtin(cmd_name) == 1)
		return (cmd->is_builtin = 1, 0);
	if (ft_strchr(cmd_name, '/'))
		return (handle_direct_path(cmd_name, cmd));
	path_env = get_env_value("PATH", env_list);
	paths = ft_split(path_env, ':');
	return (search_in_paths(paths, cmd_name, cmd));
}
