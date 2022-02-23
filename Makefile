# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 16:35:05 by jtaravel          #+#    #+#              #
#    Updated: 2022/02/23 15:00:38 by jtaravel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	./classics/ft_split.c ./classics/ft_strjoin.c \
	./srcs/ft_error.c ./srcs/ft_utils.c \
	pipex.c \

SRCS_BONUS = ./classics/ft_putstrlen.c ./classics/ft_split.c \
	     ./classics/ft_strjoin.c ./classics/ft_strncmp.c \
	     ./srcs/ft_error.c ./srcs/ft_utils_bonus.c \
	     pipex_bonus.c \

OBJS =	${SRCS:.c=.o}

OBJS_BONUS =	${SRCS_BONUS:.c=.o}

HEADERS =	includes

NAME =	pipex

NAME_BONUS = pipex_bonus


CC =	gcc

RM =	rm -f

CFLAGS =	-Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I${HEADERS} -c $< -o ${<:.c=.o}


${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

bonus:		${OBJS_BONUS}
		${CC} ${CFLAGS} ${OBJS_BONUS} -o ${NAME_BONUS}

all:		${NAME}

clean:
		${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
		${RM} ${NAME} ${NAME_BONUS}

re:		fclean all

.PHONY:		all clean flcean re
