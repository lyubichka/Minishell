/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:43:53 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/11 22:08:08 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_operator(char c, char *delimiters)
{
	if (ft_strchr(delimiters, (int)c) != NULL)
		return (1);
	return (0);
}

int is_delimiter_quoted(const char *delimiter_raw, const char* delimiter_cut)
{
	if (ft_strlen(delimiter_cut) < ft_strlen(delimiter_raw))
		return (1);
	else
		return (0);
}

char	*join_path(const char *dir, const char *cmd)
{
	char	*full_path;
	int		len_dir;
	int		len_cmd;
	int		needs_slash;
	size_t	total_len;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	if (dir[len_dir - 1] != '/')
		needs_slash = 1;
	else
		needs_slash = 0;
	total_len = len_dir + needs_slash + len_cmd + 1;
	full_path = malloc(len_dir + needs_slash + len_cmd + 1);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, total_len);
	if (needs_slash)
		ft_strlcat(full_path, "/", total_len);
	ft_strlcat(full_path, cmd, total_len);
	return (full_path);
}

char	*remove_quotes(const char *s)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"'))
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			else
				res[j++] = s[i];
		}
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}