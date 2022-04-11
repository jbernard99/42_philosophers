# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 10:17:03 by jbernard          #+#    #+#              #
#    Updated: 2022/04/11 11:09:34 by jbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CINCLUDES = -pthread

NAME = philo
HEADER = philosophers.h
SRC = main.c \
	routine.c \
	activity.c \
	input_validation.c \
	init.c \
	tools.c

all: ${NAME}

${NAME}: ${SRC}
	${CC} ${CFLAGS} ${CINCLUDES} ${SRC} -o ${NAME}

.SILENT:
clean:
	rm -rf ${NAME}
	echo "Cleaned"

fclean: clean

re: fclean all
	echo "Remake Complete!"%