/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:58:17 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/22 22:28:02 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_operator(t_token **tokens, char *line, int *line_pos,
		char *delimiters)
{
	int		j;
	char	*extract;
	t_token	*new_token;

	j = *line_pos;
	while (line[j] != '\0')
	{
		if (is_operator(line[j + 1], delimiters) == 1)
			j++;
		else
			break ;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	new_token = lst_token_create('o', extract);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

static void	extract_word(t_token **tokens, char *line, int *line_pos,
		char *delimiters)
{
	int		j;
	char	quote;
	char	*extract;
	t_token	*new_token;

	j = *line_pos;
	while (line[j] != '\0' && !is_operator(line[j], delimiters))
	{
		if (is_quote(line[j]))
		{
			quote = line[j];
			j++;
			while (line[j] != '\0')
			{
				if (line[j++] == quote)
					break ;
			}
			continue ;
		}
		j++;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos);
	new_token = lst_token_create('w', extract);
	lst_token_add_back(new_token, tokens);
	*line_pos = j;
}

static int	check_operators(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == 'o')
		{
			if (ft_strncmp((tokens->value), "<", 2) == 0
				|| ft_strncmp((tokens->value), ">", 2) == 0
				|| ft_strncmp((tokens->value), ">>", 3) == 0)
				tokens->type = 'r';
			else if (ft_strncmp((tokens->value), "<<", 3) == 0)
				tokens->type = 'h';
			else if (ft_strncmp((tokens->value), "|", 2) == 0)
				tokens->type = 'p';
			else
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					2);
				ft_putchar_fd(tokens->value[0], 2);
				ft_putstr_fd("'\n", 2);
				exit_static_status(2);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	tokenizer(t_token **tokens, char *line, char *delimiters)
{
	int	i;

	i = 0;
	if (line_has_only_space(line) == 1)
		return (-1);
	while (line[i] != '\0')
	{
		if (is_operator(line[i], delimiters) == 1)
			extract_operator(tokens, line, &i, delimiters);
		else
			extract_word(tokens, line, &i, delimiters);
	}
	token_split(tokens);
	token_cleanup(tokens);
	token_index(*tokens);
	if (check_operators(*tokens) == -1 || syntax_check(*tokens) == -1)
	{
		lst_clear_tokens(tokens);
		return (-1);
	}
	return (1);
}
