CC = cc
FLAGS = -Wall -Wextra -Werror -g
EXTRA_FLAGS = -lreadline
NAME = minishell
BNAME = minishell_bonus

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
PURPLE = \033[0;35m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RED = \033[0;31m
RESET = \033[0m

SRCS = 	$(shell ls ./my_library/libft/*.c) \
		$(shell ls ./my_library/ft_printf/*.c) \
		$(shell ls ./my_library/get_next_line/*.c) \
		$(shell ls ./execution/builtins/*c) \
		$(shell ls ./execution/utils/*c) \
		$(shell ls ./execution/executables/*c) \
		$(shell ls ./execution/redirections/*c) \
		$(shell ls ./execution/pipex/*c) \
		./main.c \



OFILES = $(SRCS:.c=.o)
BOFILES = $(BONUS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OFILES)
	@$(CC) $(FLAGS) $(OFILES) $(EXTRA_FLAGS) -o $(NAME)
	@echo "$(GREEN)Minishel compiled successfully!$(RESET)"


bonus: $(BNAME)

$(BNAME): $(BOFILES)
	@$(CC) $(FLAGS) $(BOFILES) $(MLX_FLAGS) -o $(BNAME)
	@echo "$(GREEN)So_long bonus compiled successfully!$(RESET)"

clean:
	@rm -f $(OFILES) $(BOFILES)
	@echo "$(YELLOW)Cleaning object files$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BNAME)
	@echo "$(YELLOW)Cleaning executables$(RESET)"

re: fclean all

re_bonus : fclean bonus

.PHONY: all bonus clean fclean re
