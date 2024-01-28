# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 10:33:36 by asemsey           #+#    #+#              #
#    Updated: 2024/01/28 15:31:44 by asemsey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -lpthread

SRC = main.c init.c libft.c 
TEST = cube.c

$(NAME): $(SRC)
	cc $(CFLAGS) $(SRC) -o $(NAME)

test: clean $(TEST)
	cc $(CFLAGS) $(TEST) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
