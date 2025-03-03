/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:58:17 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/03 18:53:14 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	find_quote(char *line, int i)
// {
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\'' || line[i] == '\"')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }



// static int	find_operator(char *line, int i, char *delimiters)
// {
// 	while (line[i] != '\0')
// 	{
// 		if (ft_strchr(delimiters, (int)line[i]) != NULL)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

static void extract_quote(t_token **tokens, char* line, int *line_pos)
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
			break;
		j++;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	new_token = token_create('w', extract);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

static void extract_operator(t_token **tokens, char *line, int *line_pos, char *delimiters)
{
	int		j;
	char 	*extract;
	t_token *new_token;

	j = *line_pos;
	while (line[j] != '\0')
	{
		if(is_operator(line[j + 1], delimiters) == 1)
			j++;
		else
			break;
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
	int 	j;
	char 	*extract;
	t_token	*new_token;

	j = *line_pos;
	while (line[j] != '\0')
	{
		if(is_quote(line[j + 1]) && line[j] != '\\')
			break;
		else if(is_operator(line[j + 1], delimiters) && line[j] != '\\')
			break;
		else
			j++;
	}
	extract = ft_substr(line, *line_pos, j - *line_pos + 1);
	new_token = token_create('w', extract);
	lst_token_add_back(new_token, tokens);
	if (line[j] != '\0')
		*line_pos = j + 1;
	else
		*line_pos = j;
}

void lst_token_append(t_token *new_elem, t_token *tmp1, t_token *tmp2)
{
	tmp1->next = new_elem;
	new_elem->next = tmp2;
}

void token_append(t_token *tmp1, t_token *tmp2)
{
	char	**tmp_array;
	int		i;
	t_token *new_elem;

	i = 0;
	tmp_array = ft_split(tmp1->value, ' ');
	if (tmp_array && tmp_array[0])
	{
		while(tmp_array[i])
		{
			new_elem = lst_token_create('o', tmp_array[i]);
			lst_token_append(new_elem, tmp1, tmp2);
			tmp1 = new_elem;
			i++;
		}
		free(tmp_array);
	}
}

void token_split(t_token **tokens)
{
	t_token	*tmp1;
	t_token *tmp2;

	tmp1 = *tokens;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if(tmp1->type == 'o' && ft_strchr(tmp1->value, ' ') != NULL)
			token_append(tmp1, tmp2);
		tmp1 = tmp2;
	}
}

void	token_cleanup(t_token **tokens, char *delimiters)
{
	token_split(tokens);
}

void	tokenizer(t_token **tokens, char *line, char *delimiters)
{
	int	i;
	int	end_token;

	i = 0;
	// while (line[i] != '\0')
	// {
	// 	if (find_quote(line, i) < find_operator(line, i, delimiters) && find_quote(line, i) != -1)
	// 		extract_quote(tokens, line, &i);
	// 	else if (find_operator(line, i, delimiters) != -1)
	// 		extract_operator(tokens, line, &i);
	// 	else
	// 		extract_word(tokens, line, &i);
	// }
	while (line[i] != '\0')
	{
		if (is_quote(line[i]) == 1)
			extract_quote(tokens, line, &i);
		else if (is_operator(line[i], delimiters) == 1)
			extract_operator(tokens, line, &i, delimiters);
		else
			extract_word(tokens, line, &i, delimiters);
	}
	token_cleanup(tokens, delimiters);
}