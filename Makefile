# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 10:33:36 by asemsey           #+#    #+#              #
#    Updated: 2024/02/18 14:19:14 by asemsey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -lpthread #-fsanitize=thread -g

SRC = main.c init.c libft.c t_philo.c t_fork.c time.c mutex_funcs.c survive.c sim_loop.c
#TEST = mutex_test.c cube.c

all: $(NAME)

$(NAME): $(SRC)
	cc $(CFLAGS) $(SRC) -o $(NAME)

test: clean $(TEST)
	cc $(CFLAGS) $(TEST) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all