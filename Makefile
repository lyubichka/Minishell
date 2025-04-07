NAME			= minishell

INCLUDES_FILES	= includes/minishell.h

CC				= CC

CFLAGS			= -Wall -Wextra -Werror

RM				= rm -rf

LIBFT			= libft/libft.a

RLFLAGS			= -lreadline -lhistory

RLDIR			= -L/opt/vagrant/embedded/lib

RLINC			= -I/opt/vagrant/embedded/include/readline/readline.h

SRCS_FILES		= 	char_tools.c \
					check_quotes.c \
					command_parse.c \
					envp_to_list.c \
					first_is_pipe.c \
					init_signal.c \
					lst_add.c

SRCS_DIR		= ./srcs/

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS			= $(SRCS:c=o)

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(INCLUDES_FILES) $(LIBFT) $(RLDIR) $(RLINC) $(RLFLAGS) -o $(NAME)

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