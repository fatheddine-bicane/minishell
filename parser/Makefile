CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
NAME = parse_test
SRC = parse_test.c $(shell find ./tokenization ./ast -depth -maxdepth 1 -type f -name "*.c")
LIBS = -lreadline
OBJ = $(SRC:.c=.o)
LIBFT_NAME = libsn/libsn.a
NAME_TEST = test_unit
SRC_TEST = $(shell find ./tokenization ./ast ./tests -depth -maxdepth 1 -type f -name "*.c")
OBJ_TEST = $(SRC_TEST:.c=.o)

all: $(NAME)

libft: $(LIBFT_NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME) $(LIBS)

$(NAME_TEST): $(LIBFT_NAME) $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) $(LIBFT_NAME) -o $(NAME_TEST) $(LIBS)

$(LIBFT_NAME):
	$(MAKE) -C ./libsn

run: re
	./$(NAME)

test: $(NAME_TEST)
	./$(NAME_TEST)
	@rm $(NAME_TEST)

clean:
	$(MAKE) -C ./libsn clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C ./libsn fclean
	rm -f $(NAME)

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./ignore_readline.supp -s ./$(NAME)

re: fclean all

.PHONY: clean leaks
