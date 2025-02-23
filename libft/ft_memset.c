/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:08:42 by saherrer          #+#    #+#             */
/*   Updated: 2024/06/30 21:59:37 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	d;
	size_t			i;

	d = (unsigned char)c;
	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = d;
		i++;
	}
	return (b);
}
