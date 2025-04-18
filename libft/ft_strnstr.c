/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:41:26 by saherrer          #+#    #+#             */
/*   Updated: 2024/07/01 20:31:00 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	i;
	size_t	j;

	h = (char *)haystack;
	n = (char *)needle;
	i = 0;
	if (n[i] == '\0' || (h == NULL && len == 0))
		return (h);
	while (h[i] != '\0' && i < len)
	{
		j = 0;
		while (h[i + j] == n[j] && n[j] != '\0' && h[i + j] != '\0' && i
			+ j < len)
			j++;
		if (n[j] == '\0')
			return (h + i);
		i++;
	}
	return (NULL);
}
