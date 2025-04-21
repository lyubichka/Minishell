/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:03:06 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/21 20:05:15 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_clear_tokens(t_token **tokens)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = *tokens;
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

	tmp1 = *env;
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
		if (tmp1->fd_in >= 0)
		{
			close(tmp1->fd_in);
			tmp1->fd_in = -1;
		}
		if (tmp1->fd_out >= 0)
		{
			close(tmp1->fd_out);
			tmp1->fd_out = -1;
		}
		if (tmp1->last_hd_fd >= 0)
		{
			close(tmp1->last_hd_fd);
			tmp1->last_hd_fd = -1;
		}
		free(tmp1);
		tmp1 = tmp2;
	}
	*commands = NULL;
}
