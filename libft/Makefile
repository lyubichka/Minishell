MY_SOURCES	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

MY_OBJECTS 	= ${MY_SOURCES:.c=.o}

NAME		= libft.a

CFLAGS		= -Wall -Wextra -Werror

CC			= cc

AR			= ar rcs	

LIB			= ranlib

RM			= rm -f

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c -I. $< -o ${<:.c=.o}

${NAME}:	${MY_OBJECTS}
			${AR} ${NAME} ${MY_OBJECTS}
			${LIB} ${NAME}

clean:
			${RM} ${MY_OBJECTS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all