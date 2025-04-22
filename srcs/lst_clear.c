/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:03:06 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 19:04:40 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_clear_tokens(t_token **tokens)
{
	t_token	*tmp1;
	t_token	*tmp2;

	if (!tokens || !*tokens)
		return ;
	tmp1 = *tokens;
	tmp2 = NULL;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (tmp1->value)
			free(tmp1->value);
		tmp1->value = NULL;
		free(tmp1);
		tmp1 = NULL;
		tmp1 = tmp2;
	}
	*tokens = NULL;
}

void	lst_clear_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	if (!env || !*env)
		return ;
	tmp1 = *env;
	tmp2 = NULL;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (tmp1->name)
			free(tmp1->name);
		tmp1->name = NULL;
		if (tmp1->value)
			free(tmp1->value);
		tmp1->value = NULL;
		free(tmp1);
		tmp1 = NULL;
		tmp1 = tmp2;
	}
	*env = NULL;
}

static void	close_fds(t_command *cmd)
{
	if (cmd->fd_in >= 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out >= 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	if (cmd->last_hd_fd >= 0)
	{
		close(cmd->last_hd_fd);
		cmd->last_hd_fd = -1;
	}
}

void	lst_clear_commands(t_command **commands)
{
	t_command	*tmp1;
	t_command	*tmp2;

	tmp1 = *commands;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (tmp1->argv)
			free_split(tmp1->argv);
		if (tmp1->path)
			free(tmp1->path);
		tmp1->argv = NULL;
		tmp1->path = NULL;
		close_fds(tmp1);
		free(tmp1);
		tmp1 = tmp2;
	}
	*commands = NULL;
}
