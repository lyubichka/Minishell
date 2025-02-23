/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:44:13 by saherrer          #+#    #+#             */
/*   Updated: 2024/06/30 21:44:58 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	char	c;
	size_t	i;

	if (n > 0)
	{
		ptr = (char *) s;
		c = 0;
		i = 0;
		while (i < n)
		{
			ptr[i] = c;
			i++;
		}
	}
}
