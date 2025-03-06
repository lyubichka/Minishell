/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:22:13 by veronikalub       #+#    #+#             */
/*   Updated: 2025/03/06 21:01:11 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(char **args)
{
    int n_flag;
    int i;

    n_flag = 0;
    i = 1;
    if (args[1] && ft_strcmp(args[1], "-n") == 0) // Check the flag -n
    {
        n_flag = 1;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1); 
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (!n_flag)
        write(1, "\n", 1);
    return (0);
}

// test.
// 1: No flag
// mini shell> echo Hello World
// Hello World

// 2: With the flag -n
// mini shell > echo -n Hello World
// Hello World%

// 3: Empty input
// mini shell> echo