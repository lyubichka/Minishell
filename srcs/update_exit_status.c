/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:19:11 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 22:02:09 by saherrer         ###   ########.fr       */
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
