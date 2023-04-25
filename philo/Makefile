# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 16:02:08 by tedelin           #+#    #+#              #
#    Updated: 2023/04/25 20:01:56 by ale-sain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

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