NAME			= minishell

SRCS_FILES		= main.c

SRCS_DIR		= srcs/

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

# OBJS			= $(SRCS_FILES:c=o)

INCLUDES_FILES	= minishell.h

INCLUDES_DIR	= includes/

CC				= CC

CFLAGS			= -Wall -Wextra -Werror

RM				= rm -rf

LIBFT			= -L libft -lft

