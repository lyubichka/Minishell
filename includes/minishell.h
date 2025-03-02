/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:36:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/02 21:45:09 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*value;
	char			*name;
	struct s_env	*next;
} 					t_env;

typedef struct s_token
{
	char			type; //command,argument,operatior, pipe, redirect
	char			*value; //> echo ls 
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	
	struct s_command	*next;
}	t_command;

//lst
t_env *lst_create_envp(char *env_name, char	*env_value);
void lst_add_back(t_env *new, t_env **lst);
t_token *token_create(char type, char *value);
void token_add_back(t_token *new, t_token **lst);

//signals
void	init_signal(void);

//others
void shlvl_increase (t_env **env_list);
int	check_quotes(char *line);
int	is_quote(char c);
int	is_operator(char c, char *delimiters);

#endif