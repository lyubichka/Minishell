/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:28:16 by saherrer          #+#    #+#             */
/*   Updated: 2024/06/30 21:40:47 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	char	c;
	size_t	i;

	ptr = (char *) malloc(size * count);
	if (!ptr)
		return (NULL);
	c = 0;
	i = 0;
	while (i < (count * size))
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}
