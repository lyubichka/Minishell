/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:18:20 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 19:01:06 by saherrer         ###   ########.fr       */
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
	(*commands)->last_hd_fd = -1;
	(*commands)->last_file_pos = -1;
	(*commands)->found_heredoc = 0;
	(*commands)->argv = NULL;
	(*commands)->path = NULL;
	(*commands)->next = NULL;
	(*commands)->prev = NULL;
}

static int	link_commands(t_command *cmd1, t_command *cmd2)
{
	int	pipe_fd[2];

	if (!cmd1 || !cmd2)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	if (cmd1->fd_out < 0 && cmd1->is_redir_error == 0)
	{
		cmd1->fd_out = pipe_fd[1];
		cmd1->pipe_out = 1;
	}
	else
		close(pipe_fd[1]);
	if (cmd2->fd_in < 0 && cmd2->is_redir_error == 0)
	{
		cmd2->fd_in = pipe_fd[0];
		cmd2->pipe_in = 1;
	}
	else
		close(pipe_fd[0]);
	return (0);
}

static int	create_and_link_command(t_command **curr, t_command **prior,
		t_command **head)
{
	init_command(curr);
	if (!*curr)
		return (-1);
	if (!*head)
		*head = *curr;
	else
	{
		(*prior)->next = *curr;
		(*curr)->prev = *prior;
	}
	return (0);
}

static int	handle_pipe_between_commands(t_command *prev, t_command *curr)
{
	if (prev && prev->is_redir_error != 1)
		if (link_commands(prev, curr) == -1)
			return (-1);
	return (0);
}

int	tokens_to_command(t_command **commands, t_token **tokens,\
						t_env **env_list, t_shell *shell)
{
	t_token		*tmp_token;
	t_command	*curr_cmd;
	t_command	*prev_cmd;

	tmp_token = *tokens;
	curr_cmd = NULL;
	prev_cmd = NULL;
	while (tmp_token)
	{
		if (create_and_link_command(&curr_cmd, &prev_cmd, commands) == -1)
			return (-1);
		if (command_parse(curr_cmd, &tmp_token, env_list, shell) == -1)
			return (-1);
		if (handle_pipe_between_commands(prev_cmd, curr_cmd) == -1)
			return (-1);
		if (tmp_token)
		{
			tmp_token->type = 'd';
			tmp_token = tmp_token->next;
		}
		prev_cmd = curr_cmd;
	}
	token_cleanup(tokens);
	shell->tokens = *tokens;
	return (0);
}
