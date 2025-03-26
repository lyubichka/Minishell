/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:12:48 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/26 20:37:17 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char *error_token, t_env **env_list)
{
	ft_putstr_fd("syntax error near unexpected token: '",2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd(" ' \n", 2);
	update_exit_status(2, env_list);
	return (-1);
}

char *remove_quotes(char *str)
{
	int	len;
	char	*new_str;

	len = ft_strlen(str);
	if (len >= 2 && (str[0] = '"' || str[0] == '\'') && str[len - 1] == str[0])
	{
		new_str = ft_strchr(str + 1, len - 2);
		return (new_str);
	}
	else
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	
}

int	add_to_argv(t_token *token, t_command *command)
{
	char	*cleaned;
	int		i;
	int		j;
	char	**new_argv;
	
	i = 0;
	if (token->quote != 0)
	{
		cleaned = remove_quotes(token->value);
		free(token->value);
		token->value = cleaned;
	}
	if (command->argv == NULL)
	{
		command->argv = malloc(sizeof(char *) * 2);
		if(!(command->argv))
			return(-300);
		command->argv[0] = ft_strdup(token->value);
		command->argv[1] = NULL;
		return (0);
	}
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
	token->type = 'd';
	return (0);
}

int	command_parse(t_command *command, t_token **tokens, t_env **env_list)
{
	t_token	*tmp_token;
	t_token *prev_tmp_token;
	int		tokens_processed;
	int		status;
	
	tokens_processed = 0;
	status = 0;
	tmp_token = *tokens;
	prev_tmp_token = tmp_token;
	while (tmp_token)
	{
		var_expansion(tmp_token, *env_list);
		if (tmp_token->type != 'w' && (tokens_processed == 0 || prev_tmp_token->type != 'w'))
			status = -1;
		else if (tmp_token->type == 'p')
		{
			status = 0;
			break;
		}
		else if (tmp_token->type == 'w')
			status = add_to_argv(tmp_token, command);
		else if (tmp_token->type == 'r')
			status = handle_redir(&tmp_token, &tokens_processed, command, env_list);
		else if (tmp_token->type == 'h')
			status = handle_heredoc(&tmp_token, &tokens_processed, command, env_list);
		if (status == -1)
		{
			syntax_error(tmp_token->value, env_list);
			break;
		}
		prev_tmp_token = tmp_token;
		tmp_token = tmp_token->next;
		tokens_processed++;

		//first check for errors on files, in the order that they are given, but do not exit the line. 
		//for example if i have ls -l < fdd | ls  < output, the second pipe still runs although the first put up an error		
		//if all files are ok, only then we check for the command themselves, same as above with the pipes
		//an error of a command execution it should trigger an exit, only publish a command not found for that pipe
	}
	token_cleanup(tokens);
	return (status);
}
