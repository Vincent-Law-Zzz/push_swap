# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 20:18:18 by aapollo           #+#    #+#              #
#    Updated: 2021/06/29 23:32:22 by aapollo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = push_swap

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./libft/

SRCS = 	push_swap.c 

OBJS = ${SRCS:.c=.o}

all: ${NAME}

debug: CFLAGS += -fsanitize=address -g
debug: all;

$(NAME) :${OBJS}
		${CC} ${CFLAGS} ${OBJS} -lft ./libft/libft.a -L ./libft/ -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME} 

re: fclean all
