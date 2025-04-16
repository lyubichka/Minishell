/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:18:20 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/16 20:16:48 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_command(t_command **commands)
{
	(*commands) = (t_command *)malloc(sizeof(t_command));
	if (!*commands)
		*commands = NULL;
	(*commands)->fd_in = -1;
	(*commands)->fd_out = -1;
	(*commands)->pipe_in = 0;
	(*commands)->pipe_out = 0;
	(*commands)->is_pipe = 0;
	(*commands)->is_builtin = 0;
	(*commands)->is_redir_error = 0;
	(*commands)->last_hd_pos = -1;
	(*commands)->last_hd_fd = -300;
	(*commands)->last_file_pos = -1;
	(*commands)->argv = NULL;
	(*commands)->path = NULL;
	(*commands)->next = NULL;
	(*commands)->prev = NULL;
}

int link_commands(t_command *cmd1, t_command *cmd2)
{
	int pipe_fd[2];

	if (!cmd1 || !cmd2)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	// Only assign if no redirection has already been set
	if (cmd1->fd_out == -1 && cmd1->is_redir_error == 0)
	{
		cmd1->fd_out = pipe_fd[1];
		cmd1->pipe_out = 1;
	}
	else
		close(pipe_fd[1]);

	if (cmd2->fd_in == -1 && cmd2->is_redir_error == 0)
	{
		cmd2->fd_in = pipe_fd[0];
		cmd2->pipe_in = 1;
	}
	else
		close(pipe_fd[0]);
	return (0);
}


int	tokens_to_command(t_command **commands, t_token **tokens, t_env **env_list)
{
	t_token		*tmp_token;
	t_command	*current_cmd;
	t_command	*prior_cmd;
	
	tmp_token = *tokens;
	current_cmd = NULL;
	prior_cmd = NULL;
	while(tmp_token)
	{
		init_command(&current_cmd);
		if (!current_cmd)
			return (-1);
		if (!*commands)
			*commands = current_cmd;
		else
		{
			prior_cmd->next = current_cmd;
			current_cmd->prev = prior_cmd;
		}
		if (command_parse(current_cmd, &tmp_token, env_list) == -1)
			return(-1);
		if (prior_cmd && prior_cmd->is_redir_error != 1)
		{
			if (link_commands(prior_cmd, current_cmd) == -1)
				return(-1);
		}
		if (tmp_token)
		{
			tmp_token->type = 'd';
			tmp_token = tmp_token->next;
		}
		prior_cmd = current_cmd;
	}
	token_cleanup(tokens);
	return (0);
}
