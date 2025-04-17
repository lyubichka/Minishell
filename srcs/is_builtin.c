/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:31:12 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/17 21:58:55 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0 ||
		ft_strncmp(cmd, "echo", 5) == 0 ||
		ft_strncmp(cmd, "env", 4) == 0 ||
		ft_strncmp(cmd, "pwd", 4) == 0 ||
		ft_strncmp(cmd, "export", 7) == 0 ||
		ft_strncmp(cmd, "unset", 6) == 0 ||
		ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
