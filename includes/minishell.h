/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:36:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/21 22:10:40 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_shell
{
	struct s_env		*env_list;
	struct s_token		*tokens;
	struct s_command	*commands;
}						t_shell;

typedef struct s_env
{
	char				*value;
	char				*name;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				type;
	char				*value;
	int					id;
	struct s_token		*next;
}						t_token;

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
	int					found_heredoc;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

// add_to_argv.c
int						add_to_argv(t_token *token, t_command *cmd,
							t_env **env_list);

// cd.c
int						ft_cd(char **args, t_env **env);

// char_tools.c
int						is_quote(char c);
int						is_operator(char c, char *delimiters);
int						is_delimiter_quoted(const char *delimiter_raw,
							const char *delimiter_cut);
char					*join_path(const char *dir, const char *cmd);

// check_quotes.c
int						check_quotes(char *line);

// child_processes.c
void					run_builtin(t_command *cmd, t_env **env_list, t_shell *shell_info);
void					run_external_command(t_command *cmd, t_env **env_list, t_shell *shell);

// command_parse.c
int						command_parse(t_command *command, t_token **tokens,
							t_env **env_list, t_shell *shell);

// custom_signals.c
void					ign_signals(void);
void					handle_heredoc_sig(int sig);

// echo.c
int						ft_echo(char **args);

// env_list_to_array.c
char					**env_list_to_array(t_env *env_list);

// env.c
int						ft_env(t_env **env);

// envp_to_list.c
char					*get_env_value(char *name, t_env *env);
int						envp_to_list(char **envp, t_env **env_list);

// executor.c
void					execute_command(t_command *cmd, t_env **env_list, t_shell *shell_info);

// exit.c
void					ft_exit(char **args, t_shell *shell);

// export.c
int						ft_export(char **args, t_env **env);

// find_exec_path.c
int						find_exec_path(char *cmd_name, t_env *env_list,
							t_command *cmd);

// handle_redir.c
int						handle_redir(t_token **tmp_token, t_command *cmd,
							t_env **env_list);

// here_doc_child.c
void					handle_heredoc_child(int *pipe_fd, char *delimiter,
							int is_quoted, t_env *env);

// here_doc.c
int						handle_heredoc(t_token *token, t_command *command,
							t_env **env_list);

// init_signal.c
void					init_signal(void);

// is_builtin.c
int						is_builtin(char *cmd);

// line_var_expansion.c
void					line_var_expansion(char **line_to_expand,
							t_env *env_list);

// lst_add.c
void					lst_add_front(t_env *new, t_env **lst);
void					lst_add_back(t_env *new, t_env **lst);
void					lst_token_add_back(t_token *new, t_token **lst);

// lst_append_del.c
void					lst_token_append(t_token *new_elem, t_token *tmp1,
							t_token *tmp2);

// lst_clear.c
void					lst_clear_tokens(t_token **tokens);
void					lst_clear_env(t_env **env);
void					lst_clear_commands(t_command **commands);

// lst_create.c
t_env					*lst_create_envp(char *env_name, char *env_value);
t_token					*lst_token_create(char type, char *value);

// memory_free.c
void					free_split(char **array);
void					shell_cleanup(t_shell *shell, int exit_code, int env_flag);

// parent_exit_message.c
void					parent_exit_status(int status);

// parse_exec_line.c
void					parse_exec_line(t_env **env_list, char *new_line,
							t_shell *shell_info);
t_shell					*get_shell_info(t_shell *set_shell);

// pwd.c
int						ft_pwd(t_env **env_list);

// remove_quotes.c
char					*remove_quotes(const char *s);

// shlvl_increase.c
void					shlvl_increase(t_env **env_list);

// syntax_check.c
int						syntax_error(char *error_token);
int						syntax_check(t_token *tokens);
int						line_has_only_space(char *line);

// token_clean_split.c
void					token_split(t_token **tokens);
void					token_cleanup(t_token **tokens);
void					token_index(t_token *tokens);

// tokenizer.c
int						tokenizer(t_token **tokens, char *line,
							char *delimiters);

// tokens_to_command.c
int						tokens_to_command(t_command **commands,	t_token **tokens, 
							t_env **env_list, t_shell *shell);

// unset.c
int						ft_unset(char **args, t_env **env);

// update_exit_status.c
int						exit_static_status(int set_status);
int						handle_cd_error(char *target_dir);

// var_expansion.c
void					var_expansion(t_token *token, t_env *env_list);

#endif
