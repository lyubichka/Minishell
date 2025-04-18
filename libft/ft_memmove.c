/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:14:14 by saherrer          #+#    #+#             */
/*   Updated: 2024/06/30 21:58:23 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		i;

	ptr_dst = (char *)dst;
	ptr_src = (const char *)src;
	i = 0;
	if ((ptr_src + len <= ptr_dst || ptr_dst < ptr_src) && (ptr_src != NULL
			|| ptr_dst != NULL))
	{
		while (i < len)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	}
	else if (ptr_src != NULL || ptr_dst != NULL)
	{
		while (len > 0)
		{
			ptr_dst[len - 1] = ptr_src[len - 1];
			len--;
		}
	}
	return (dst);
}
