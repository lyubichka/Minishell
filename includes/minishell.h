/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:36:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/03/03 20:08:12 by saherrer         ###   ########.fr       */
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

//signals
void	init_signal(void);

//others
void	shlvl_increase (t_env **env_list);
int		check_quotes(char *line);
int		is_quote(char c);
int		is_operator(char c, char *delimiters);

//lst
t_env	*lst_create_envp(char *env_name, char	*env_value);
void	lst_add_back(t_env *new, t_env **lst);
t_token	*lst_token_create(char type, char *value);
void	lst_token_add_back(t_token *new, t_token **lst);
void	lst_token_append(t_token *new_elem, t_token *tmp1, t_token *tmp2);
void	lst_token_del(t_token *prev, t_token *curr, t_token *forw);
void	lst_clear_tokens(t_token **tokens);


void	token_split(t_token **tokens);
void	token_cleanup(t_token **tokens);
int		tokenizer(t_token **tokens, char *line, char *delimiters);



#endif