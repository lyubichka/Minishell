/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:19:11 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 22:33:20 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_static_status(int set_status)
{
	static int	exit_status;

	if (set_status != -1)
		exit_status = set_status;
	return (exit_status);
}

int	handle_cd_error(char *target_dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target_dir, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit_static_status(1);
	return (1);
}
