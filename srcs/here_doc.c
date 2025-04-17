/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:50:36 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 23:41:53 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_parent(int *pipe_fd, pid_t pid, int *status)
{
	close(pipe_fd[1]);
	waitpid(pid, status, 0);
	init_signal();
	if (WIFEXITED(*status) && (WEXITSTATUS(*status) == 1))
	{
		exit_static_status(1);
		close(pipe_fd[0]);
		return (-1);
	}
	else
		return (pipe_fd[0]);
}

static int	fork_one_heredoc(char *delimiter, t_env *env, int is_quoted)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	

	if (pipe(pipe_fd) == -1)
		return (-1);
	ign_signals();
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return(-1);
	}
	if (pid == 0)
	{
		handle_heredoc_child(pipe_fd, delimiter, is_quoted, env);
		return (0);
	}
	else
		return (handle_heredoc_parent(pipe_fd, pid, &status));
}

static void	update_token_heredoc(t_token* token, t_command* command, int fd)
{
	command->last_hd_fd = fd;
	command->last_hd_pos = token->id;
	token->type = 'd';
	token->next->type = 'd';
}

int handle_heredoc(t_token *token, t_command *command, t_env **env_list)
{
	char 	*delimiter;
	int		fd;
	
	while (token && token->type != 'p')
	{
		if (token->type == 'h')
		{
			if (!token->next || token->next->type != 'w')
				return -300; //syntax error
			delimiter = remove_quotes(token->next->value);
			fd = fork_one_heredoc(delimiter, *env_list, \
				is_delimiter_quoted(token->next->value, delimiter));
			free(delimiter);
			if (fd < 0)
				return (-1);
			if (command->last_hd_fd != -300 && command->last_hd_fd != -1)
				close(command->last_hd_fd);
			update_token_heredoc(token, command, fd);
			token = token->next;
		}
		token = token->next;
	}
	return (0);
}
