/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:20:35 by saherrer          #+#    #+#             */
/*   Updated: 2024/07/02 20:24:25 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char d)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != d && (!s[i + 1] || s[i + 1] == d))
			word_count++;
		i++;
	}
	return (word_count);
}

static void	word_creator(char *word, char *str_w, char d)
{
	int	i;

	i = 0;
	while (str_w[i] != '\0' && str_w[i] != d)
	{
		word[i] = str_w[i];
		i++;
	}
	word[i] = '\0';
}

static void	*ft_memfree(char **ret, int k)
{
	while (k > 0)
	{
		free(ret[k - 1]);
		k--;
	}
	free (ret);
	return (NULL);
}

static char	**array_creator(char **ret, char *str, char d)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == d)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != d && str[i + j] != '\0')
				j++;
			ret[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (!ret[k])
				return (ft_memfree(ret, k));
			word_creator(ret[k++], str + i, d);
			i = i + j;
		}
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		word_count;
	char	*str;

	str = (char *)s;
	word_count = ft_word_count(s, c);
	ret = (char **)malloc(sizeof(char *) * word_count + sizeof(NULL));
	if (!ret)
		return (NULL);
	ret = array_creator(ret, str, c);
	if (ret == NULL)
		return (NULL);
	ret[word_count] = NULL;
	return (ret);
}
