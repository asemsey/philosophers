NAME = philo

CFLAGS = -Wall -Wextra -Werror -lpthread

SRC = main.c init.c t_philo.c t_fork.c time.c mutex_funcs.c \
		survive.c sim_loop.c monitor.c

all: $(NAME)

$(NAME): $(SRC)
	cc $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re