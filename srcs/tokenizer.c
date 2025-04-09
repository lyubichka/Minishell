/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:58:17 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/09 21:54:00 by saherrer         ###   ########.fr       */
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
			j++;  // Skip escaped quote
		else if (line[j] == quote)  // Found closing quote
		{
			j++;  // Move past closing quote
			if (is_quote(line[j])) // Check if a new quote starts immediately
			{
				quote = line[j]; // Set new quote type
				continue;  // Restart the loop without breaking
			}
			else
				break;  // Stop scanning if no more consecutive quotes
		}
		j++;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	// if (quote == '\'')
	// 	new_token = token_create('w', extract, 1);
	// else
		new_token = token_create('w', extract); // need to review this "is quote" in the end of the token
	lst_token_add_back(new_token, tokens);
	// if (line[j] != '\0')
	// 	*line_pos = j + 1;
	// else
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
	new_token = token_create('o', extract);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

static void	extract_word(t_token *tokens, char *line, int *line_pos, char *delimiters)
{
	int		j;
	char	quote;
	char	*extract;
	t_token	*new_token;

	j = *line_pos;
	while (line[j] != '\0' && !is_operator(line[j], delimiters))  // Stop only on operators
	{
		if (is_quote(line[j]))  // Found opening quote
		{
			quote = line[j];
			j++;  // Move past opening quote
			while (line[j] != '\0')
			{
				if (line[j] == '\\' && (line[j + 1] == quote))
					j++;  // Skip escaped quote
				else if (line[j] == quote)  // Found closing quote
				{
					j++;  // Move past closing quote
					break;
				}
				j++;
			}
			continue;  // Continue scanning after handling the quote
		}
		j++;
	}
	// Extract the full word, including quoted sections
	extract = ft_substr(line, *line_pos, j - *line_pos);
	new_token = token_create('w', extract);
	lst_token_add_back(new_token, tokens);
	// Move position forward
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
				exit_static_status(1);
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
			extract_quote(tokens, line, &i); //need to fix it to remove the need to check for escaped quotes as not needed in the subject
		else if (is_operator(line[i], delimiters) == 1)
			extract_operator(tokens, line, &i, delimiters);
		else
			extract_word(tokens, line, &i, delimiters);
	}
	token_split(tokens);
	token_cleanup(tokens);
	token_index(*tokens);
	if (check_operators(*tokens) == -1 || pipe_syntax_check(*tokens) == -1)
	{
		lst_clear_tokens(tokens);
		return (-1);
	}
	return (1);
}
