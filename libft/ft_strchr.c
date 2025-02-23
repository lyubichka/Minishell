/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:54:02 by saherrer          #+#    #+#             */
/*   Updated: 2024/07/02 20:16:37 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			d;
	char			*src;
	unsigned int	i;

	i = 0;
	d = (char) c;
	src = (char *) s;
	while (src[i] != '\0' && src[i] != d)
		i++;
	if (src[i] == '\0' && d != '\0')
		return (NULL);
	return (src + i);
}
