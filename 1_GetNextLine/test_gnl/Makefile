# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 22:04:39 by mbourgeo          #+#    #+#              #
#    Updated: 2022/08/15 20:42:39 by mbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= get_next_line.c \
			get_next_line_utils.c \
			main.c \

BONUS	= get_next_line_bonus.c \
			get_next_line_utils_bonus.c \
			main_bonus.c \

OBJS	= ${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS:.c=.o}

NAME	= prog

CC		= cc

#STD		= -std=c17
#DEBUG		= -g3 -fsanitize=address

RM		= rm -f

CFLAGS	 = -Wall -Wextra -Werror -g

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${DEBUG} -o ${NAME} ${OBJS}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

main.o:		get_next_line.h

clean:
			${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		$(OBJS) $(BONUS_OBJS)
			${CC} ${DEBUG} -o ${NAME} $(BONUS_OBJS)

.PHONY:		all clean fclean re bonus
