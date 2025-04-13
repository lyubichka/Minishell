/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:27:06 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/11 21:46:42 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void update_command(t_command *command, int fd_in, int fd_out)
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

static int handle_input_redir(const char *filename, t_command *cmd, t_token **tmp_token)
{
	int fd_in;
	
	fd_in = open(filename, O_RDONLY, 0);
	if (fd_in == -1)
	{
		ft_putstr_fd("minishell> ", 2);
		perror(filename);
	}
	update_command(cmd, fd_in, 0);
	if (fd_in == -1)
	{
		exit_static_status(1);
		// update_exit_status(1, env_list);
		cmd->is_redir_error = 1;
		return (-1);
	}
	(*tmp_token)->type = 'd';
	(*tmp_token)->next->type = 'd';
	*tmp_token = (*tmp_token)->next;
	return (0);
}

static int	handle_append_redir(const char *filename, t_command *cmd, t_token **tmp_token)
{
	int		fd_out;

	fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("minishell> ", 2);
		perror(filename);
	}
	update_command(cmd, 0, fd_out);
	if (fd_out == -1)
	{
		exit_static_status(1);
		// update_exit_status(1, env_list);
		cmd->is_redir_error = 1;
		return (-1);
	}
	(*tmp_token)->type = 'd';
	(*tmp_token)->next->type = 'd';
	*tmp_token = (*tmp_token)->next;
	return (0);
}

static int	handle_trunc_redir(const char *filename, t_command *cmd, t_token **tmp_token)
{
	int		fd_out;

	fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("minishell> ", 2);
		perror(filename);
	}
	update_command(cmd, 0, fd_out);
	if (fd_out == -1)
	{
		exit_static_status(1);
		// update_exit_status(1, env_list);
		cmd->is_redir_error = 1;
		return (-1);
	}
	(*tmp_token)->type = 'd';
	(*tmp_token)->next->type = 'd';
	*tmp_token = (*tmp_token)->next;
	return (0);
}

int	handle_redir(t_token **tmp_token,t_command *cmd, t_env **env_list)
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
	var_expansion((*tmp_token)->next, *env_list);
	filename = remove_quotes((*tmp_token)->next->value);
	if (!filename)
		return (-1);
	if ((*tmp_token)->value[0] == '<') 
		return(handle_input_redir(filename, cmd, tmp_token));
	else if ((*tmp_token)->value[0] == '>' && (*tmp_token)->value[1] != '>') // Output trunc redirection
		return (handle_trunc_redir(filename, cmd, tmp_token));
	else if ((*tmp_token)->value[0] == '>' && (*tmp_token)->value[1] == '>') // Output append redirection
		return (handle_append_redir(filename, cmd, tmp_token));
    return 0; // Return 0 to continue parsing
}