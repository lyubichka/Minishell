/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:09:58 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/21 23:19:49 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	any_heredoc(t_token *tokens)
{
	t_token	*tmp_token;

	tmp_token = tokens;
	while (tmp_token)
	{
		if (tmp_token->type == 'p')
			return (0);
		if (tmp_token->type == 'h')
			return (1);
		tmp_token = tmp_token->next;
	}
	return (0);
}

static void	decide_fd_in(t_command *command)
{
	if (command->last_hd_fd >= 0 && command->last_file_pos != 0)
	{
		if (command->last_hd_pos > command->last_file_pos)
		{
			if (command->fd_in >= 0)
			{
				close(command->fd_in);
				command->fd_in = -1;
			}
			command->fd_in = command->last_hd_fd;
		}
		else
		{
			if (command->last_hd_fd >= 0)
				close(command->last_hd_fd);
		}
	}
	else if (command->last_hd_fd >= 0)
		command->fd_in = command->last_hd_fd;
	else if (command->fd_in >= 0)
		return ;
	else if (command->pipe_in == 1)
		command->fd_in = -1;
	// else
	// 	command->fd_in = STDIN_FILENO;
}

static int	handle_token_loop(t_token **tmp_token, t_command *cmd,
		t_env **env_list, t_shell *shell)
{
	int	status;

	(void)shell;
	status = 0;
	while (cmd && *tmp_token && status == 0)
	{
		if ((*tmp_token)->type == 'p')
		{
			cmd->is_pipe = 1;
			break ;
		}
		if (cmd->found_heredoc == 1)
		{
			status = handle_heredoc(*tmp_token, cmd, env_list);
			cmd->found_heredoc = -1;
		}
		if ((*tmp_token)->type == 'w')
			status = add_to_argv(*tmp_token, cmd, env_list);
		else if ((*tmp_token)->type == 'r')
			status = handle_redir(tmp_token, cmd, env_list);
		*tmp_token = (*tmp_token)->next;
	}
	return (status);
}

int	command_parse(t_command *cmd, t_token **tokens, t_env **env_list, t_shell *shell)
{
	t_token	*tmp_token;
	int		status;

	status = 0;
	tmp_token = *tokens;
	cmd->found_heredoc = any_heredoc(*tokens);
	status = handle_token_loop(&tmp_token, cmd, env_list, shell);
	if (status == -300)
		return (syntax_error(tmp_token->value));
	if (cmd->argv && cmd->argv[0] && cmd->is_redir_error == 0)
		status = find_exec_path(cmd->argv[0], *env_list, cmd);
	// if (status == -1)
	//	clear everything ? but do not return (-1 as execution would continue);
	decide_fd_in(cmd);
	*tokens = tmp_token;
	return (0);
}

/* first check for errors on files, in the order that they are given,
	but do not exit the line.
	for example if i have ls -l < fdd | ls  < output,
	the second pipe still runs although the first put up an error
	if all files are ok, only then we check for the command themselves,
	same as above with the pipes
	an error of a command execution it should trigger an exit,
	only publish a command not found for that pipe
	File redirection takes precedence over the pipe for stdout.
	also to keep in mind that if a file fails,
	the rest does not apply. So for example, if ls >a <d and d does not exist
	it will erase everything on a but then fail and not rewrite a,
	if I had ls <d >a, then it would not get to erase a.
	if I face a syntax error (for example 2 consecutive redir),
	i wont execute anything and just publish a syntax error message
	in the case of heredoc, i need to allow all heredocs to run,
	but i will still respect the presedence of left to right
	in heredoc, if the delimiter is quoted, the body is not expanded,
	meaning that if put a $USER while typing it wont expant
	the delimiter itself should be quote removed
	[n]<<[-]word
		here-document
	delimiter
	No parameter and variable expansion, command substitution,
	arithmetic expansion, or filename expansion is
	performed on word. If any part of word is quoted,
	the delimiter is the result of quote removal on word, and the lines
	in the here-document are not expanded.
	If word is unquoted,
	all lines of the here-document are subjected to parameter expansion
*/
