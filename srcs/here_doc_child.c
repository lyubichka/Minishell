/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:40:19 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/18 18:01:59 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_write_read(char *delimiter, int write_end, int is_quoted,
		t_env *env)
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
			free(new_line);
			new_line = NULL;
			break ;
		}
		write_line = ft_strjoin(new_line, "\n");
		if (is_quoted == 0)
			line_var_expansion(&write_line, env);
		write(write_end, write_line, ft_strlen(write_line));
		free(new_line);
		new_line = NULL;
		free(write_line);
		write_line = NULL;
	}
	close(write_end);
}

void	handle_heredoc_child(int *pipe_fd, char *delimiter, int is_quoted,
		t_env *env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_sig);
	close(pipe_fd[0]);
	heredoc_write_read(delimiter, pipe_fd[1], is_quoted, env);
	// check the need of clearing all memory at this point
	exit(0);
}
