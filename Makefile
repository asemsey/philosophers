# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 10:33:36 by asemsey           #+#    #+#              #
#    Updated: 2024/02/04 10:25:50 by asemsey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -lpthread

SRC = main.c init.c libft.c t_philo.c t_fork.c live.c
TEST = cube.c

$(NAME): $(SRC)
	cc $(CFLAGS) $(SRC) -o $(NAME)

test: clean $(TEST)
	cc $(CFLAGS) $(TEST) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
