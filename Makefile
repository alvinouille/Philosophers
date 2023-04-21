# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvina <alvina@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 16:02:08 by tedelin           #+#    #+#              #
#    Updated: 2023/04/21 19:21:50 by alvina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra 

CC = cc

SRC = forked.c life.c init.c utils.c clean_check.c main.c utils2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ) Makefile
			$(CC) $(CFLAGS) -I ./ -o $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re