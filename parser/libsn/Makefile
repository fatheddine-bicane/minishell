CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = libsn.a
SRCS = $(shell find . -type f -name "*.c")
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)

all: $(NAME)

%.o: %.c
	@$(CC) -c $(FLAGS) $< -o $@
	@ar rcs $(NAME) $@

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean re fclean
