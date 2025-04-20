/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_exit_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:08:45 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/20 19:25:53 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_exit_status(int status)
{
	char	*text_to_write;

	if (WTERMSIG(status) == SIGINT)
		write(2, "\n", 1);
	if (WIFEXITED(status))
		exit_static_status(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGSEGV)
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit: \n", 8);
			else
			{
				write(2, "Segmentation fault: ", 20);
				text_to_write = ft_itoa(WTERMSIG(status));
				write(2, text_to_write, ft_strlen(text_to_write));
				free(text_to_write);
				write(2, "\n", 1);
			}
			exit_static_status(WTERMSIG(status) + 128);
		}
	}
}
