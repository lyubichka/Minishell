/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:20:04 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/07 20:43:28 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	replace_var(t_token *token, char *var_value, char *str, int *pos_value)
// {
// 	char	*old_token_value;
// 	char	*new_token_value;
// 	char	*tmp;

// 	old_token_value = ft_strdup(token->value);
// 	free(token->value);
// 	tmp = ft_substr(old_token_value, 0, *pos_value);
// 	new_token_value = ft_strjoin(tmp, var_value);
// 	free (tmp);
// 	tmp = ft_substr(old_token_value, *pos_value + ft_strlen(str) + 1, ft_strlen(old_token_value) - ft_strlen(str) - *pos_value - 1);
// 	token->value = ft_strjoin(new_token_value, tmp);
// 	free(tmp);
// 	free(new_token_value);
// 	free(old_token_value);
	
// }

static void	var_not_found(t_token *token, char *str, int *pos_value)
{
	char	*new_token_value;
	int		prefix_len;
	int		suffix_start;
	int		total_len;

	prefix_len = *pos_value;
	suffix_start = *pos_value + ft_strlen(str) + 1;
	total_len = prefix_len + ft_strlen(token->value + suffix_start);
	new_token_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if(!new_token_value)
		return ;
	ft_strlcpy(new_token_value, token->value, prefix_len + 1);
	ft_strlcat(new_token_value, token->value + suffix_start, total_len + 1);
	free(token->value);
	token->value = new_token_value;
}

static void	replace_var(t_token *token, char *var_value, char *str, int *pos_value)
{
	char	*new_token_value;
	int		prefix_len;
	int		var_len;
	int		suffix_start;
	int		total_len;

	prefix_len = *pos_value;
	var_len = ft_strlen(var_value);
	suffix_start = *pos_value + ft_strlen(str) + 1;
	total_len = prefix_len + var_len + ft_strlen(token->value + suffix_start);
	new_token_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_token_value)
		return;
	ft_strlcpy(new_token_value, token->value, prefix_len + 1);
	ft_strlcat(new_token_value, var_value, total_len + 1);
	ft_strlcat(new_token_value, token->value + suffix_start, total_len + 1);
	free(token->value);
	token->value = new_token_value;
	*pos_value = prefix_len + var_len;
	
}

static void	find_and_expand(t_token *token, t_env *env_list, int *pos_value)
{
	int j;
	char *str;
	
	j = *pos_value;
	while(token->value[j] != '\0' && token->value[j] != ' ')
		j++;
	str = ft_substr(token->value, *pos_value + 1, j - *pos_value - 1);
	while (env_list && ft_strncmp(env_list->name, str, ft_strlen(str)) != 0)
		env_list = env_list->next;
	if (env_list)
		replace_var(token, env_list->value, str, pos_value);
	else
		var_not_found(token, str, pos_value);
	free(str);
}

void	var_expansion(t_token *token, t_env *env_list)
{
	int	i;

	i = 0;
	if(token->quote == 1)
		return ;
	while(token->value[i] != '\0')
	{
		if(token->value[i] == '$' && token->value[i + 1] != '\0' && token->value[i + 1] != ' ')
		{
			if(i == 0 || token->value[i - 1] != '\\' )
			{
				find_and_expand(token, env_list, &i);
				continue;
			}
		}
		i++;
	}
}