/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:58:58 by saherrer          #+#    #+#             */
/*   Updated: 2024/07/06 21:29:26 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		i;

	ptr_dst = (char *) dst;
	ptr_src = (const char *) src;
	i = 0;
	while (i < n && (dst != NULL || src != NULL))
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}
