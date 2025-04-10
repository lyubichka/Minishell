/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:24:18 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/04 04:24:21 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Checks whether the string is a valid numeric argument.
 * str is the string to check.
 * ret 1 if the string is a number, 0 if not.
 */
static int is_numeric_arg(char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++; // Skip the sign
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

/**
* Built-in exit command for shell shutdown.
 * args Array of arguments (args[0] — "exit", args[1] — exit code, if any).
* env Pointer to the environment list to update $?.
* ret Does not return a value, terminates the program.
 */
void ft_exit(char **args, t_env **env)
{
    int exit_code;

    ft_putstr_fd("exit\n", 1); // Notification of withdrawal
    if (!args[1])
    {
        set_exit_status(env, 0);
        exit(0);
    }
    if (!is_numeric_arg(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        set_exit_status(env, 2);
        exit(2);
    }
    if (args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        set_exit_status(env, 1);
        return; // We do not exit, the shell continues to work
    }
    exit_code = ft_atoi(args[1]);
    set_exit_status(env, exit_code % 256); // Updating the exit status
    exit(exit_code % 256); // Output with a modulo 256 code
}

/*
* Tests to verify ft_exit performance:
*
* # 1. Exit without arguments
 * minishell> exit
 * # Expected output: "exit" in stdout
 * # Result: Shell exits with code 0
*
* #2. Output with a numeric argument
 * minishell> exit 42
 * # Expected output: "exit" in stdout
 * # Result: Shell exits with code 42
 *
 * # 3. Output with a non-numeric argument
 * minishell> exit abc
* # Expected output: "exit\nminishell: exit: abc: numeric argument required" in stderr
 * # Result: Shell exits with code 2
*
* # 4. Too many arguments
 * minishell> exit 42 43
 * # Expected output: "exit\nminishell: exit: too many arguments" in stderr
 * # Check: minishell > echo $?
* # Expected output: 1
* # Result: Shell continues to work
*
* #5. Exit with a negative number
* minishell> exit -1
 * # Expected output: "exit" in stdout
 * # Result: Shell terminates with code 255 (modulo 256)
 */