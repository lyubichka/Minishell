/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:47:47 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 23:05:15 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*make_env_string(t_env *env, char **array, int i)
{
	char	*name_eq;
	char	*full_str;

	name_eq = ft_strjoin(env->name, "=");
	if (!name_eq)
	{
		while (i > 0)
		free(array[--i]);
		free(array);
		return (NULL);
	}
	full_str = ft_strjoin(name_eq, env->value);
	free(name_eq);
	if (!full_str)
	{
		while (i > 0)
			free(array[--i]);
		free(array);
		return (NULL);
	}
	return (full_str);
}

char	**env_list_to_array(t_env *env_list)
{
	char		**array;
	int			count;
	char 		*full_str; 
	int  		i;

	i = 0;
	count = count_env_vars(env_list);
	array = malloc((sizeof(char *)) * (count + 1));
	if (!array)
		return (NULL);
	while (env_list)
	{
		full_str = make_env_string(env_list, array, i);
		if (!full_str)
			return (NULL);
		array[i++] = full_str;
		env_list = env_list->next;
	}
	array[count] = NULL;
	return (array);
}
