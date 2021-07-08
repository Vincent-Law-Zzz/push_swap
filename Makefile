
.PHONY: all clean fclean re

NAME = push_swap

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./libft/

SRCS = 	push_swap.c ps_utils.c ps_utils2.c ps_utils3.c algorithm_p1.c \
		algorithm_p2.c comb5.c exit.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

debug: CFLAGS += -fsanitize=address -g
debug: fclean all;

dvs: CFLAGS += -g
dvs: fclean all;

tools:
	make -C ./libft/

$(NAME) :${OBJS} | tools
		${CC} ${CFLAGS} ${OBJS} -lft ./libft/libft.a -L ./libft/ -o ${NAME}

clean:
		rm -f ${OBJS}
		make -C ./libft/ clean

fclean:	clean
		rm -f ${NAME}
		make -C ./libft/ fclean

re: fclean all
