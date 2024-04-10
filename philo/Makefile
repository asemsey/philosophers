
NAME = philo

CFLAGS = -Wall -Wextra -Werror -lpthread #-fsanitize=thread -g

SRC = main.c init.c t_philo.c t_fork.c time.c mutex_funcs.c \
		survive.c sim_loop.c monitor.c
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