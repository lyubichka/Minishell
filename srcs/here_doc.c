/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:50:36 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/15 20:57:04 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_write_read(char *delimiter, int write_end, int is_quoted, t_env *env)
{
	char	*write_line;
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (!new_line)
			break ;
		if (ft_strncmp(delimiter, new_line, ft_strlen(delimiter) + 1) == 0)
		{
			free (new_line);
			new_line = NULL;
			break ;
		}
		write_line = ft_strjoin(new_line, "\n");
		fprintf(stderr, "DEBUG: before to write: [%s]\n", write_line);
		if (is_quoted == 0)
			line_var_expansion(&write_line, env);
		fprintf(stderr, "DEBUG: About to write: [%s]\n", write_line);
		write(write_end, write_line, ft_strlen(write_line));
		free(new_line);
		new_line = NULL;
		free(write_line);
		write_line = NULL;
	}
	close(write_end);
}

static void	handle_heredoc_child(int *pipe_fd, char *delimiter, int is_quoted, t_env *env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_sig);
	close(pipe_fd[0]);
	heredoc_write_read(delimiter, pipe_fd[1], is_quoted, env);
	//check the need of clearing all memory at this point
	exit(0);
}

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
			command->last_hd_fd = fd;
			command->last_hd_pos = token->id;
			token->type = 'd';
			token->next->type = 'd';
			token = token->next;
		}
		token = token->next;
	}
	return (0);
}
