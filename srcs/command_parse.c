/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:09:58 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/07 22:18:47 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char *error_token, t_env **env_list)
{
	ft_putstr_fd("syntax error near unexpected token: '",2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd(" ' \n", 2);
	// update_exit_status(2, env_list);
	exit_static_status(2);
	return (-1);
}

char	*remove_quotes(const char *s)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"'))
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			else
				res[j++] = s[i];
		}
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	add_to_argv(t_token *token, t_command *command, t_env **env_list)
{
	char	*cleaned;
	int		i;
	int		j;
	char	**new_argv;
	
	i = 0;
	var_expansion(token, *env_list);
	cleaned = remove_quotes(token->value);
	free(token->value);
	token->value = cleaned;
	if (command->argv == NULL)
	{
		command->argv = malloc(sizeof(char *) * 2);
		if(!(command->argv))
			return(-300);
		command->argv[0] = ft_strdup(token->value);
		command->argv[1] = NULL;
		return (0);
	}
	else
	{
		while (command->argv[i] != NULL)
			i++;
		new_argv = (char **)malloc(sizeof (char *) * (i + 2));
		if (!new_argv)
			return (-300);
		while (j < i)
		{
			new_argv[j] = command->argv[j];
			j++;
		}
		new_argv[i] = ft_strdup(token->value);
		new_argv[i + 1] = NULL;
		free(command->argv);
		command->argv = new_argv;
	}
	token->type = 'd';
	return (0);
}

// int open_file(const char *filename, int flags, mode_t mode)
// {
// 	int fd = open(filename, flags, mode);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("Error opening file", 2);
// 	}
// 	return fd;
// }

int handle_input_redir(const char *filename)
{
	int fd;
	
	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_putstr_fd("minishell> ", 2);
		perror(filename);
	}
	return fd;
}

int handle_output_redir(const char *filename, int append)
{
	int fd;
	
	if (append == 1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell> ", 2);
			perror(filename);
		}
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell> ", 2);
			perror(filename);
		}
	}
	return fd;
}

void update_command(t_command *command, int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
	    if (command->fd_in != -300 && command->fd_in != -1)
			close(command->fd_in); // Close old fd_in
		command->fd_in = fd_in;
	}
	if (fd_out != 0)
	{
		if (command->fd_out != -300 && command->fd_out != -1)
			close(command->fd_out); // Close old fd_out
		command->fd_out = fd_out;
	}
}

int	handle_redir(t_token **tmp_token,t_command *command, t_env **env_list)
{
	int fd_in;
	int fd_out;
	int stop_parsing; // Flag to stop parsing after error
	char *filename;

	fd_in = 0;
	fd_out = 0;
	stop_parsing = 0;
	if ((*tmp_token)->next == NULL || (*tmp_token)->next->type != 'w')
		return -300; // Redirection Error --> all further parsing should stop. Need to evaluate how and when are we closing the fd

	// Get the filename (next token after redirection operator)
	filename = (*tmp_token)->next->value;

	// Expand variables and remove quotes from the filename
	var_expansion(&(*tmp_token)->next, *env_list);
	filename = remove_quotes(filename); //recheck memory loss here

	// Process input redirection
	if ((*tmp_token)->value[0] == '<') 
	{
		fd_in = handle_input_redir(filename);
		update_command(command, fd_in, 0);
		if (fd_in == -1)
		{
			exit_static_status(1);
			// update_exit_status(1, env_list);
			command->is_redir_error == 1;
			return (-1);
		}
		(*tmp_token)->type = 'd';
		(*tmp_token)->next->type = 'd';
		*tmp_token = (*tmp_token)->next; // Move to the next token after the redirection
	}
	// Process output redirection
	else if ((*tmp_token)->value[0] == '>' && (*tmp_token)->value[1] != '>') // Output redirection
	{
		fd_out = handle_output_redir(filename, 0);
		update_command(command, 0, fd_out);
		if (fd_out == -1)
		{
			exit_static_status(1);
			// update_exit_status(1, env_list);
			command->is_redir_error == 1;
			return (-1);
		}
		(*tmp_token)->type = 'd';
		(*tmp_token)->next->type = 'd';
		*tmp_token = (*tmp_token)->next; // Move to the next token after the redirection
	}
	// Process append output redirection
	else if ((*tmp_token)->value[0] == '>' && (*tmp_token)->value[1] == '>') // Output append redirection
	{
		fd_out = handle_output_redir(filename, 1);
		update_command(command, 0, fd_out);
		if (fd_out == -1)
		{
			exit_static_status(1);
			// update_exit_status(1, env_list);
			command->is_redir_error == 1;
			return (-1);
		}
		(*tmp_token)->type = 'd';
		(*tmp_token)->next->type = 'd';
		*tmp_token = (*tmp_token)->next; // Move to the next token after the redirection
    }
    return 0; // Return 0 to continue parsing
}

int is_delimiter_quoted(const char *delimiter_raw, const char* delimiter_cut)
{
	if (ft_strlen(delimiter_cut) < ft_strlen(delimiter_raw))
		return (1);
	else
		return (0);
}

void	heredoc_write_read(char *delimiter, int write_end)
{
	char	*write_line;
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (!new_line)
			break ;
		if (ft_strncmp(delimiter, new_line, ft_strlen(delimiter)) == 0)
		{
			free (new_line);
			new_line = NULL;
			break ;
		}
		write_line = ft_strjoin(new_line, "\n");
		//maybe expand here?
		write(write_end, write_line, ft_strlen(write_line));
		free(new_line);
		new_line = NULL;
		free(write_line);
		write_line = NULL;
	}
	close(write_end);
}

int	fork_one_heredoc(char *delimiter, t_env *env, int is_quoted)
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
		//child process
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_heredoc_sig);
		close(pipe_fd[0]);
		heredoc_write_read(delimiter, pipe_fd[1]);
		//check the need of clearing all memory at this point
	}
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
			if (is_delimiter_quoted(token->next->value, delimiter) == 1)
				fd = fork_one_heredoc(delimiter, *env_list, 1);
			else
				fd = fork_one_heredoc(delimiter, *env_list, 0);
			free(delimiter);
			if (fd < 0)
				return (-1);
			if (command->last_hd_fd != -300 && command->last_hd_fd != -1)
				close(command->last_file_pos);
			command->last_hd_fd = fd;
			command->last_hd_pos = token->id;
			token->type = 'd';
			token->next->type = 'd';
			token = token->next;
		}
		token = token->next;
	}
}

int	any_heredoc(t_token *tokens)
{
	t_token *tmp_token;

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

int	command_parse(t_command *command, t_token **tokens, t_env **env_list)
{
	t_token	*tmp_token;
	int		status;
	int 	found_heredoc;
	
	status = 0;
	tmp_token = *tokens;
	found_heredoc == any_heredoc(*tokens);
	while (command && tmp_token && status == 0) 
	{
		if (tmp_token->type == 'p')
			break;
		if (found_heredoc == 1)
		{
			status = handle_heredoc(tmp_token, command, env_list);
			found_heredoc == -1;
		}
		if (tmp_token->type == 'w')
			status = add_to_argv(tmp_token, command, env_list);
		else if (tmp_token->type == 'r')
			status = handle_redir(&tmp_token, command, env_list); //treat files, fd_in, fd_out and redirs
		tmp_token = tmp_token->next;

		//first check for errors on files, in the order that they are given, but do not exit the line. 
		//for example if i have ls -l < fdd | ls  < output, the second pipe still runs although the first put up an error		
		//if all files are ok, only then we check for the command themselves, same as above with the pipes
		//an error of a command execution it should trigger an exit, only publish a command not found for that pipe
		//File redirection takes precedence over the pipe for stdout.
		//also to keep in mind that if a file fails, the rest does not apply. So for example, if ls >a <d and d does not exist
		//it will erase everything on a but then fail and not rewrite a, if I had ls <d >a, then it would not get to erase a.
		//if I face a syntax error (for example 2 consecutive redir), i wont execute anything and just publish a syntax error message
		// in the case of heredoc, i need to allow all heredocs to run, but i will still respect the presedence of left to right
		// in heredoc, if the delimiter is quoted, the body is not expanded, meaning that if put a $USER while typing it wont expant
		// the delimiter itself should be quote removed
		/*	[n]<<[-]word
        		here-document
			delimiter
		*/
		//No parameter and variable expansion, command substitution, arithmetic expansion, or filename expansion is 
		//performed on word. If any part of word is quoted, the delimiter is the result of quote removal on word, and the lines
		//in the here-document are not expanded. 
		//If word is unquoted, all lines of the here-document are subjected to parameter expansion
		
	}
	if (status == -300)
	{
		syntax_error(tmp_token->value, env_list); // here would need to close all open fds.
		return (-1);
	}
	token_cleanup(tokens);
	return (0);
}
