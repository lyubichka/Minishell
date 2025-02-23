/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:13:28 by saherrer          #+#    #+#             */
/*   Updated: 2024/07/01 21:05:15 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_check(char c, char const *trim_set)
{
	int	i;

	i = 0;
	while (trim_set[i] != '\0')
	{
		if (trim_set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;

	start = 0;
	i = 0;
	while (char_check(s1[start], set) == 1 && s1[start] != '\0')
		start++;
	end = ft_strlen(s1);
	if (end != start)
	{
		while (char_check(s1[end - 1], set) == 1 && end != -1)
			end--;
	}
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	while (s1[start + i] != '\0' && (start + i) < end)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
