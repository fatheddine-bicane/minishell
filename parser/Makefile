CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = parse_test
SRC = parse_test.c $(shell find ./tokenization -depth -maxdepth 1 -type f -name "*.c")
LIBS = -lreadline
OBJ = $(SRC:.c=.o)
LIBFT_NAME = libsn/libsn.a

all: $(NAME)

libft: $(LIBFT_NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME) $(LIBS)

$(LIBFT_NAME):
	$(MAKE) -C ./libsn

run: re
	./$(NAME)

clean:
	$(MAKE) -C ./libsn clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C ./libsn fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
