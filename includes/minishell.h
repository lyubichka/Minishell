/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:36:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/11 22:09:16 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_env
{
	char			*value;
	char			*name;
	struct s_env	*next;
} 					t_env;

typedef struct s_token
{
	char			type; //word or operator (w for word / r for redirect / p for pipe / d for delete / h for heredoc)
	char			*value; //> echo ls 
	int				id;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	char				**argv;
	char				*path;
	int					fd_in;
	int					fd_out;
	int					pipe_in;
	int					pipe_out;
	int					is_pipe;
	int					is_builtin;
	int					is_redir_error;
	int					last_file_pos;
	int					last_hd_pos;
	int					last_hd_fd;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

// add_to_argv.c
int		add_to_argv(t_token *token, t_command *cmd, t_env **env_list);

// char_tools.c
int		is_quote(char c);
int		is_operator(char c, char *delimiters);
int		is_delimiter_quoted(const char *delimiter_raw, \
			const char* delimiter_cut);
char	*join_path(const char *dir, const char *cmd);
char	*remove_quotes(const char *s);

//check_quotes.c
int		check_quotes(char *line);

// find_exec_path.c
int		find_exec_path(char *cmd_name, t_env *env_list, t_command *cmd);

// handle_redir.c
int		handle_redir(t_token **tmp_token,t_command *cmd, t_env **env_list);

// here_doc.c
int		handle_heredoc(t_token *token, t_command *command, t_env **env_list);


//signals
void	init_signal(void);
void 	ign_signals(void);
void	handle_heredoc_sig(int sig);

//others
void	shlvl_increase (t_env **env_list);




int		exit_static_status(int set_status);
int		syntax_error(char *error_token);
int		syntax_check(t_token *tokens);
void	free_split(char **array);

//lst
t_env	*lst_create_envp(char *env_name, char	*env_value);
void	lst_add_back(t_env *new, t_env **lst);
void	lst_add_front(t_env *new, t_env **lst);
t_token *lst_token_create(char type, char *value);
void	lst_token_add_back(t_token *new, t_token **lst);
void	lst_token_append(t_token *new_elem, t_token *tmp1, t_token *tmp2);
void	lst_token_del(t_token *prev, t_token *curr, t_token *forw);
void	lst_clear_tokens(t_token **tokens);

int		envp_to_list(char **envp, t_env **env_list);
void	update_exit_status(int status, t_env **env_list);

void	token_split(t_token **tokens);
void	token_cleanup(t_token **tokens);
void	token_index(t_token *tokens);
int		tokenizer(t_token **tokens, char *line, char *delimiters, t_env **env_list);
void	var_expansion(t_token *token, t_env *env_list);
int		command_parse(t_command *command, t_token **tokens, t_env **env_list);
int		tokens_to_command(t_command **commands, t_token **tokens, t_env **env_list);

void	line_var_expansion(char **line_to_expand, t_env *env_list);
void	parse_exec_line(t_env **env_list, char* new_line);

#endif