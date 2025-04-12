/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:18:14 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:37:50 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Outputs delimited arguments to the echo command.
 * args Array of arguments (starting from index i).
* i is the initial index for output.
 * ret 0 on success, 1 on output error.
 */
static void print_args(char **args, int i)
{
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1]) // Adding a space between the arguments
            ft_putchar_fd(' ', 1);
        i++;
    }
}

/**
* The built-in echo command for outputting arguments to stdout.
 * args Array of arguments (args[0] is "echo", args[1] is the first argument).
* env is a pointer to the environment list for status updates.
 * ret 0 on success, 1 on error.
 */
int ft_echo(char **args, t_env **env)
{
    int n_flag;
    int i;

    n_flag = 0;
    i = 1;
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        n_flag = 1;
        i++;
    }
    if (args[i])
        print_args(args, i);
    else if (!n_flag) // If there are no arguments and there is no -n, output \n
        ft_putchar_fd('\n', 1);
    else
        return (set_exit_status(env, 0), 0); // Only -n with no arguments
    if (!n_flag) // Adding a newline, if not -n
        ft_putchar_fd('\n', 1);
    exit_static_status(0);
    return (0);
}

/*
* Tests to verify the operation of ft_echo:
*
* # 1. Output without a flag -n
* minishell> echo Hello World
 * # Expected output: Hello World\n
 * minishell > echo $?
* # Expected output: 0
*
* # 2. Output with the flag -n
* minishell> echo -n Hello World
 * # Expected output: Hello World (without line feed)
* minishell > echo $?
* # Expected output: 0
*
* # 3. Empty input with no arguments
 * minishell> echo
 * # Expected output: \n (empty string)
* minishell > echo $?
* # Expected output: 0
*
* # 4. Output error (e.g. closed stdout)
 * minishell> echo Hello > /dev/full
 * # Expected output: minishell: echo: write error
 * minishell > echo $?
* # Expected output: 1
 *
* # 5. Only the -n flag with no arguments
 * minishell> echo -n
 * # Expected output: (nothing, no line feed)
* minishell > echo $?
* # Expected output: 0
 */
