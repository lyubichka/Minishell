/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:26:26 by saherrer          #+#    #+#             */
/*   Updated: 2024/07/05 20:52:45 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	size;

	i = 0;
	src_len = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len < dstsize)
		size = dst_len + src_len;
	else
		size = src_len + dstsize;
	while (src[i] != '\0' && (dst_len + 1) < dstsize)
	{
		dst[dst_len] = src [i];
		i++;
		dst_len++;
	}
	dst[dst_len] = '\0';
	return (size);
}
