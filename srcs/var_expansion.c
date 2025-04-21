/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:20:04 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/21 23:31:44 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_not_found(t_token *token, char *var_name, int *pos_value)
{
	char	*new_token_value;
	int		prefix_len;
	int		suffix_start;
	int		total_len;

	prefix_len = *pos_value;
	suffix_start = *pos_value + ft_strlen(var_name) + 1;
	total_len = prefix_len + ft_strlen(token->value + suffix_start);
	new_token_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_token_value)
		return ;
	ft_strlcpy(new_token_value, token->value, prefix_len + 1);
	ft_strlcat(new_token_value, token->value + suffix_start, total_len + 1);
	free(token->value);
	token->value = new_token_value;
	if (token->value[0] == '\0')
		token->type = 'd';
	*pos_value = prefix_len;
}

static void	replace_var(t_token *token, char *var_value, char *var_name,
		int *pos_value)
{
	char	*new_token_value;
	int		prefix_len;
	int		var_len;
	int		suffix_start;
	int		total_len;

	prefix_len = *pos_value;
	var_len = ft_strlen(var_value);
	suffix_start = *pos_value + ft_strlen(var_name) + 1;
	total_len = prefix_len + var_len + ft_strlen(token->value + suffix_start);
	new_token_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_token_value)
		return ;
	ft_strlcpy(new_token_value, token->value, prefix_len + 1);
	ft_strlcat(new_token_value, var_value, total_len + 1);
	ft_strlcat(new_token_value, token->value + suffix_start, total_len + 1);
	free(token->value);
	token->value = new_token_value;
	*pos_value = prefix_len + var_len;
}

static void	found_exit_var(t_token *token, int *pos_value)
{
	int		j;
	char	*var_name;
	char	*exit_code_str;

	j = *pos_value + 2;
	var_name = ft_substr(token->value, *pos_value + 1, j - *pos_value - 1);
	exit_code_str = ft_itoa(exit_static_status(-1));
	replace_var(token, exit_code_str, var_name, pos_value);
	free(exit_code_str);
	free(var_name);
}

static void	find_and_expand(t_token *token, t_env *env_list, int *pos_value)
{
	int		j;
	char	*var_name;

	j = *pos_value + 1;
	while (token->value[j] && (ft_isalnum(token->value[j])
			|| token->value[j] == '_'))
		j++;
	if ((j == *pos_value + 1) && token->value[j] == '$')
		j++;
	var_name = ft_substr(token->value, *pos_value + 1, j - *pos_value - 1);
	while (env_list && ft_strncmp(env_list->name, var_name, ft_strlen(var_name)
			+ 1) != 0)
		env_list = env_list->next;
	if (env_list)
		replace_var(token, env_list->value, var_name, pos_value);
	else
		var_not_found(token, var_name, pos_value);
	free(var_name);
}

void	var_expansion(t_token *token, t_env *env_list)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (token && token->value[i] != '\0')
	{
		if (token->value[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token->value[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (token->value[i] == '$' && !in_single_quote
			&& (ft_isalnum(token->value[i + 1]) || token->value[i + 1] == '?'
				|| token->value[i + 1] == '_' || token->value[i + 1] == '$'))
		{
			if (token->value[i + 1] == '?')
				found_exit_var(token, &i);
			else
				find_and_expand(token, env_list, &i);
			continue ;
		}
		i++;
	}
}
