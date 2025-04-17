/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:43:16 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 23:43:54 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_skip_quote(char c, char *quote)
{
	if (!*quote)
	{
		*quote = c;
		return (1);
	}
	else if (*quote == c)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

char	*remove_quotes(const char *s)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (is_quote(s[i]) && should_skip_quote(s[i], &quote))
			;
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
