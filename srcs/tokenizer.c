/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:58:17 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/26 21:08:55 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_quote(t_token **tokens, char *line, int *line_pos)
{
	int		j;
	char	quote;
	char	*extract;
	t_token	*new_token;

	j = *line_pos;
	quote = line[*line_pos];
	j++;
	while (line[j] != '\0')
	{
		if (line[j] == '\\' && (line[j + 1] == '\'' || line[j + 1] == '\"'))
			j++;  // Skip the escape character
		else if (line[j] == quote)  // Found closing quote
			break ;
		j++;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	if (quote == '\'')
		new_token = token_create('w', extract, 1);
	else
		new_token = token_create('w', extract, 2);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

static void	extract_operator(t_token **tokens, char *line, int *line_pos, char *delimiters)
{
	int		j;
	char 	*extract;
	t_token *new_token;

	j = *line_pos;
	while (line[j] != '\0')
	{
		if (is_operator(line[j + 1], delimiters) == 1)
			j++;
		else
			break ;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	new_token = token_create('o', extract, 0);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

static void	extract_word(t_token *tokens, char *line, int *line_pos, char *delimiters)
{
	int		j;
	char	*extract;
	t_token	*new_token;

	j = *line_pos;
	while (line[j] != '\0')
	{
		if (is_quote(line[j + 1]) && line[j] != '\\')
			break ;
		else if (is_operator(line[j + 1], delimiters) && line[j] != '\\')
			break ;
		else
			j++;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	new_token = token_create('w', extract, 0);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

static int	check_operators(t_token *tokens)
{
	while(tokens)
	{
		if(tokens->type == 'o')
		{
			if(ft_strncmp((tokens->value), "<", 2) == 0 || \
				ft_strncmp((tokens->value), ">", 2) == 0 || \
				ft_strncmp((tokens->value), ">>", 3) == 0)
				tokens->type = 'r';
			else if (ft_strncmp((tokens->value), "<<", 3) == 0)
				tokens->type = 'h';
			else if (ft_strncmp((tokens->value), "|", 2) == 0)
				tokens->type = 'p';
			else
			{
				ft_putstr_fd("Error: Unidentified operator ", 2);
				ft_putstr_fd(tokens->value, 2);
				ft_putstr_fd(" found \n", 2);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	tokenizer(t_token **tokens, char *line, char *delimiters, t_env **env_list)
{
	int	i;
	int	end_token;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_quote(line[i]) == 1)
			extract_quote(tokens, line, &i);
		else if (is_operator(line[i], delimiters) == 1)
			extract_operator(tokens, line, &i, delimiters);
		else
			extract_word(tokens, line, &i, delimiters);
	}
	token_split(tokens);
	token_cleanup(tokens);
	if (check_operators(*tokens) == -1 || first_or_last_is_pipe(*tokens) == -1)
	{
		update_exit_status(1, env_list);
		lst_clear_tokens(tokens);
		return (-1);
	}
	return (1);
}

//need to fix this to address situation like ls hello"world" so that "world" is properly expanded and not treated as a separate token