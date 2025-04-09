/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_var_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:20:04 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/09 21:02:29 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_not_found_line(char **line, char *var_name, int *pos_value)
{
	char	*new_line_value;
	int		prefix_len;
	int		suffix_start;
	int		total_len;

	prefix_len = *pos_value;
	suffix_start = *pos_value + ft_strlen(var_name) + 1;
	total_len = prefix_len + ft_strlen(*line + suffix_start);
	new_line_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if(!new_line_value)
		return ;
	ft_strlcpy(new_line_value, *line, prefix_len + 1);
	ft_strlcat(new_line_value, *line + suffix_start, total_len + 1);
	free(*line);
	*line = new_line_value;
}

static void	replace_var_line(char **line, char *var_value, char *var_name, int *pos_value)
{
	char	*new_line_value;
	int		prefix_len;
	int		var_len;
	int		suffix_start;
	int		total_len;

	prefix_len = *pos_value;
	var_len = ft_strlen(var_value);
	suffix_start = *pos_value + ft_strlen(var_name) + 1;
	total_len = prefix_len + var_len + ft_strlen(*line + suffix_start);
	new_line_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_line_value)
		return;
	ft_strlcpy(new_line_value, *line, prefix_len + 1);
	ft_strlcat(new_line_value, var_value, total_len + 1);
	ft_strlcat(new_line_value, *line + suffix_start, total_len + 1);
	free(*line);
	*line = new_line_value;
	*pos_value = prefix_len + var_len;
	
}

static void	find_and_expand_line(char **line, t_env *env_list, int *pos_value)
{
	int j;
	char *var_name;
	char *exit_code_str;
	
	j = *pos_value;
	while ((*line)[j] != '\0' && (*line)[j] != ' ' && (*line)[j] != '$')
		j++;
	var_name = ft_substr(*line, *pos_value + 1, j - *pos_value - 1);
	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		exit_code_str = ft_itoa(exit_static_status(-1));
		replace_var_line(line, exit_code_str, var_name, pos_value);
		free(exit_code_str);		
	}	
	else
	{
		while (env_list && ft_strncmp(env_list->name, var_name, ft_strlen(var_name)) != 0)
			env_list = env_list->next;
		if (env_list)	
			replace_var_line(line, env_list->value, var_name, pos_value);
		else
			var_not_found_line(line, var_name, pos_value);
	}
	free(var_name);
}

void line_var_expansion(char **line_to_expand, t_env *env_list)
{
    int i;

	i = 0;
    while ((*line_to_expand)[i] != '\0')
    {
        if ((*line_to_expand)[i] == '$')
        {
            find_and_expand_line(line_to_expand, env_list, &i);
            continue ; // Skip the rest of the loop after expansion
        }
        i++;  // Continue scanning the next character
    }
}
