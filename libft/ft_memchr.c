/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:15:29 by saherrer          #+#    #+#             */
/*   Updated: 2024/06/30 21:44:08 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*src;
	char	d;
	size_t	i;

	src = (char *)s;
	d = (char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == d)
			return (src + i);
		i++;
	}
	return (NULL);
}
