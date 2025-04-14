NAME			= minishell

INCLUDES_FILES	= includes/minishell.h

CC				= CC -g

CFLAGS			= -Wall -Wextra -Werror -Iincludes -Ilibft

RM				= rm -rf

LIBFT			= libft/libft.a

RLFLAGS			= -lreadline -lhistory

RLDIR			= -L/opt/vagrant/embedded/lib

RLINC			= -I/opt/vagrant/embedded/include

SRCS_FILES		= 	add_to_argv.c \
					cd.c \
					char_tools.c \
					check_quotes.c \
					command_parse.c \
					custom_signals.c \
					echo.c \
					env.c \
					envp_to_list.c \
					executor.c \
					exit.c \
					export.c \
					find_exec_path.c \
					handle_redir.c \
					here_doc.c \
					init_signal.c \
					line_var_expansion.c \
					lst_add.c \
					lst_append_del.c \
					lst_clear.c \
					lst_create.c \
					main.c \
					memory_free.c \
					parse_exec_line.c \
					pwd.c \
					shlvl_increase.c \
					syntax_check.c \
					token_clean_split.c \
					tokenizer.c \
					tokens_to_command.c \
					unset.c \
					update_exit_status.c \
					utils.c \
					var_expansion.c

SRCS_DIR		= ./srcs/

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS			= $(SRCS:c=o)

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RLDIR) $(RLINC) $(RLFLAGS) -o $(NAME)

$(LIBFT):
		make all -C libft

%.o: %.c
		$(CC) $(CFLAGS) $(RLINC) -c $< -o $@

clean:
		rm -f $(OBJS)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re: fclean all

.PHONY: all clean fclean re