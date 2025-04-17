/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:13:28 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/17 22:15:47 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handle(int sig)
{
	(void) sig;
	write(1, "\n", 1);  // Move to a new line
	rl_on_new_line();   // Tell Readline we are at a new line
	rl_replace_line("", 0);  // Clear the current input
	rl_redisplay();      // Redisplay the prompt
	exit_static_status(1);
}

static void sigquit_handle(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 6);  // Erase "^\" from terminal
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, sigquit_handle);
}