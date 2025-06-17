CC = cc
FLAGS = -Wall -Wextra -Werror -g
EXTRA_FLAGS = -lreadline
NAME = minishell
BNAME = minishell_bonus

GREEN = \033[0;32m
BLUE = \033[0;34m
PURPLE = \033[0;35m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RED = \033[0;31m
RESET = \033[0m

SRCS = 	./my_library/libft/ft_atoi.c ./my_library/libft/ft_bzero.c ./my_library/libft/ft_calloc.c ./my_library/libft/ft_isalnum.c ./my_library/libft/ft_isalpha.c ./my_library/libft/ft_isascii.c ./my_library/libft/ft_isdigit.c ./my_library/libft/ft_isprint.c ./my_library/libft/ft_itoa.c ./my_library/libft/ft_lstadd_back_bonus.c ./my_library/libft/ft_lstadd_front_bonus.c ./my_library/libft/ft_lstclear_bonus.c ./my_library/libft/ft_lstdelone_bonus.c ./my_library/libft/ft_lstiter_bonus.c ./my_library/libft/ft_lstlast_bonus.c ./my_library/libft/ft_lstmap_bonus.c ./my_library/libft/ft_lstnew_bonus.c ./my_library/libft/ft_lstsize_bonus.c ./my_library/libft/ft_memchr.c ./my_library/libft/ft_memcmp.c ./my_library/libft/ft_memcpy.c ./my_library/libft/ft_memmove.c ./my_library/libft/ft_memset.c ./my_library/libft/ft_putchar_fd.c ./my_library/libft/ft_putendl_fd.c ./my_library/libft/ft_putnbr_fd.c ./my_library/libft/ft_putstr_fd.c ./my_library/libft/ft_split.c ./my_library/libft/ft_strchr.c ./my_library/libft/ft_strdup.c ./my_library/libft/ft_striteri.c ./my_library/libft/ft_strjoin.c ./my_library/libft/ft_strlcat.c ./my_library/libft/ft_strlcpy.c ./my_library/libft/ft_strlen.c ./my_library/libft/ft_strmapi.c ./my_library/libft/ft_strncmp.c ./my_library/libft/ft_strnstr.c ./my_library/libft/ft_strrchr.c ./my_library/libft/ft_strtrim.c ./my_library/libft/ft_substr.c ./my_library/libft/ft_tolower.c ./my_library/libft/ft_toupper.c \
		./my_library/ft_printf/ft_nb_count.c ./my_library/ft_printf/ft_printf.c ./my_library/ft_printf/ft_putadrr.c ./my_library/ft_printf/ft_putchar.c ./my_library/ft_printf/ft_puthexa.c ./my_library/ft_printf/ft_putnbr.c ./my_library/ft_printf/ft_putstr.c ./my_library/ft_printf/ft_putunint.c \
		./my_library/get_next_line/get_next_line.c \
		./execution/builtins/cd.c ./execution/builtins/check_is_builtin.c ./execution/builtins/echo.c ./execution/builtins/env.c ./execution/builtins/exit.c ./execution/builtins/export.c ./execution/builtins/export_utils.c ./execution/builtins/pwd.c ./execution/builtins/unset.c \
		./execution/utils/free_functions.c ./execution/utils/set_env.c ./execution/utils/wait_child.c \
		./execution/executables/builtins.c ./execution/executables/executable.c ./execution/executables/execute_executable_utils.c ./execution/executables/execute_executable_utils2.c ./execution/executables/execute_executables.c ./execution/executables/is_command.c ./execution/executables/utils.c  \
		./execution/redirections/handle_redirections.c ./execution/redirections/is_redirection.c ./execution/redirections/red_out_inf.c \
		./execution/signals/signals.c ./execution/signals/sognals_heredoc.c \
		./parser/libsn/sn_atoi.c ./parser/libsn/sn_bzero.c ./parser/libsn/sn_calloc.c ./parser/libsn/sn_isalpha.c ./parser/libsn/sn_istrchr.c ./parser/libsn/sn_memcpy.c ./parser/libsn/sn_memmove.c ./parser/libsn/sn_memset.c ./parser/libsn/sn_print_nbr.c ./parser/libsn/sn_print_str.c ./parser/libsn/sn_printf.c ./parser/libsn/sn_printf_parser.c ./parser/libsn/sn_readfile.c ./parser/libsn/sn_sb.c ./parser/libsn/sn_sb_nbr.c ./parser/libsn/sn_sb_str.c ./parser/libsn/sn_sb_utils.c ./parser/libsn/sn_split.c ./parser/libsn/sn_sprintf.c ./parser/libsn/sn_strdup.c ./parser/libsn/sn_strjoin.c ./parser/libsn/sn_strlcpy.c ./parser/libsn/sn_strlen.c ./parser/libsn/sn_strncmp.c ./parser/libsn/sn_strndup.c ./parser/libsn/sn_strsearch.c ./parser/libsn/sn_substr.c \
		./parser/tokenization/checkers.c ./parser/tokenization/checkers_bonus.c ./parser/tokenization/extractors.c ./parser/tokenization/matchers.c ./parser/tokenization/scan.c ./parser/tokenization/scan_bonus.c ./parser/tokenization/token.c ./parser/tokenization/token_identify.c ./parser/tokenization/token_identify_bonus.c ./parser/tokenization/token_type_str.c \
		./parser/ast/ast_core.c ./parser/ast/ast_print.c ./parser/ast/cmd_init.c ./parser/ast/exec.c ./parser/ast/exec_utils.c ./parser/ast/extractors.c ./parser/ast/parser.c ./parser/ast/parser_bonus.c \
		./expansion/heredoc.c ./expansion/params.c ./expansion/var_expander.c ./expansion/word_split.c \
		./execution/throw_error/cd_error.c ./execution/throw_error/executable_error.c ./execution/throw_error/exit_error.c ./execution/throw_error/pipe_error.c \
		./execution/compound/compound.c \
		./execution/group/group.c \
		./execution/pipes/is_pipe.c ./execution/pipes/is_pipe_child_utils.c ./execution/pipes/is_pipe_utils.c ./execution/pipes/is_pipe_utils2.c \
		./execution/custum_prompt/custum_prompt.c \
		./execution/here_doc/handle_here_doc_utils.c ./execution/here_doc/handle_here_docs.c ./execution/here_doc/here_doc.c ./execution/here_doc/here_doc_utils.c \
		./main.c \
		./utils.c \


BONUS = 	./my_library/libft/ft_atoi.c ./my_library/libft/ft_bzero.c ./my_library/libft/ft_calloc.c ./my_library/libft/ft_isalnum.c ./my_library/libft/ft_isalpha.c ./my_library/libft/ft_isascii.c ./my_library/libft/ft_isdigit.c ./my_library/libft/ft_isprint.c ./my_library/libft/ft_itoa.c ./my_library/libft/ft_lstadd_back_bonus.c ./my_library/libft/ft_lstadd_front_bonus.c ./my_library/libft/ft_lstclear_bonus.c ./my_library/libft/ft_lstdelone_bonus.c ./my_library/libft/ft_lstiter_bonus.c ./my_library/libft/ft_lstlast_bonus.c ./my_library/libft/ft_lstmap_bonus.c ./my_library/libft/ft_lstnew_bonus.c ./my_library/libft/ft_lstsize_bonus.c ./my_library/libft/ft_memchr.c ./my_library/libft/ft_memcmp.c ./my_library/libft/ft_memcpy.c ./my_library/libft/ft_memmove.c ./my_library/libft/ft_memset.c ./my_library/libft/ft_putchar_fd.c ./my_library/libft/ft_putendl_fd.c ./my_library/libft/ft_putnbr_fd.c ./my_library/libft/ft_putstr_fd.c ./my_library/libft/ft_split.c ./my_library/libft/ft_strchr.c ./my_library/libft/ft_strdup.c ./my_library/libft/ft_striteri.c ./my_library/libft/ft_strjoin.c ./my_library/libft/ft_strlcat.c ./my_library/libft/ft_strlcpy.c ./my_library/libft/ft_strlen.c ./my_library/libft/ft_strmapi.c ./my_library/libft/ft_strncmp.c ./my_library/libft/ft_strnstr.c ./my_library/libft/ft_strrchr.c ./my_library/libft/ft_strtrim.c ./my_library/libft/ft_substr.c ./my_library/libft/ft_tolower.c ./my_library/libft/ft_toupper.c \
		./my_library/ft_printf/ft_nb_count.c ./my_library/ft_printf/ft_printf.c ./my_library/ft_printf/ft_putadrr.c ./my_library/ft_printf/ft_putchar.c ./my_library/ft_printf/ft_puthexa.c ./my_library/ft_printf/ft_putnbr.c ./my_library/ft_printf/ft_putstr.c ./my_library/ft_printf/ft_putunint.c \
		./my_library/get_next_line/get_next_line.c \
		./execution/builtins/cd.c ./execution/builtins/check_is_builtin.c ./execution/builtins/echo.c ./execution/builtins/env.c ./execution/builtins/exit.c ./execution/builtins/export.c ./execution/builtins/export_utils.c ./execution/builtins/pwd.c ./execution/builtins/unset.c \
		./execution/utils/free_functions.c ./execution/utils/set_env.c ./execution/utils/wait_child.c \
		./execution/executables/builtins.c ./execution/executables/executable.c ./execution/executables/execute_executable_utils.c ./execution/executables/execute_executable_utils2.c ./execution/executables/execute_executables.c ./execution/executables/is_command.c ./execution/executables/utils.c  \
		./execution/redirections/handle_redirections.c ./execution/redirections/is_redirection.c ./execution/redirections/red_out_inf.c \
		./execution/signals/signals.c ./execution/signals/sognals_heredoc.c \
		./parser/libsn/sn_atoi.c ./parser/libsn/sn_bzero.c ./parser/libsn/sn_calloc.c ./parser/libsn/sn_isalpha.c ./parser/libsn/sn_istrchr.c ./parser/libsn/sn_memcpy.c ./parser/libsn/sn_memmove.c ./parser/libsn/sn_memset.c ./parser/libsn/sn_print_nbr.c ./parser/libsn/sn_print_str.c ./parser/libsn/sn_printf.c ./parser/libsn/sn_printf_parser.c ./parser/libsn/sn_readfile.c ./parser/libsn/sn_sb.c ./parser/libsn/sn_sb_nbr.c ./parser/libsn/sn_sb_str.c ./parser/libsn/sn_sb_utils.c ./parser/libsn/sn_split.c ./parser/libsn/sn_sprintf.c ./parser/libsn/sn_strdup.c ./parser/libsn/sn_strjoin.c ./parser/libsn/sn_strlcpy.c ./parser/libsn/sn_strlen.c ./parser/libsn/sn_strncmp.c ./parser/libsn/sn_strndup.c ./parser/libsn/sn_strsearch.c ./parser/libsn/sn_substr.c \
		./parser/tokenization/checkers.c ./parser/tokenization/checkers_bonus.c ./parser/tokenization/extractors.c ./parser/tokenization/matchers.c ./parser/tokenization/scan.c ./parser/tokenization/scan_bonus.c ./parser/tokenization/token.c ./parser/tokenization/token_identify.c ./parser/tokenization/token_identify_bonus.c ./parser/tokenization/token_type_str.c \
		./parser/ast/ast_core.c ./parser/ast/ast_print.c ./parser/ast/cmd_init.c ./parser/ast/exec.c ./parser/ast/exec_utils.c ./parser/ast/extractors.c ./parser/ast/parser.c ./parser/ast/parser_bonus.c \
		./expansion/heredoc.c ./expansion/params.c ./expansion/var_expander.c ./expansion/word_split.c \
		./execution/throw_error/cd_error.c ./execution/throw_error/executable_error.c ./execution/throw_error/exit_error.c ./execution/throw_error/pipe_error.c \
		./execution/compound/compound.c \
		./execution/group/group.c \
		./execution/pipes/is_pipe.c ./execution/pipes/is_pipe_child_utils.c ./execution/pipes/is_pipe_utils.c ./execution/pipes/is_pipe_utils2.c \
		./execution/custum_prompt/custum_prompt.c \
		./execution/here_doc/handle_here_doc_utils.c ./execution/here_doc/handle_here_docs.c ./execution/here_doc/here_doc.c ./execution/here_doc/here_doc_utils.c \
		./main_bonus.c \
		./utils.c \



OFILES = $(SRCS:.c=.o)
BOFILES = $(BONUS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OFILES)
	@rm -f $(BNAME)
	@$(CC) $(FLAGS) $(OFILES) $(EXTRA_FLAGS) -o $(NAME)
	@echo "$(GREEN)Minishel compiled successfully!$(RESET)"

bonus: $(BNAME)

$(BNAME): $(BOFILES)
	@rm -f $(NAME)
	@$(CC) $(FLAGS) $(BOFILES) $(EXTRA_FLAGS) -o $(BNAME)
	@echo "$(GREEN)Minishell bonus compiled successfully!$(RESET)"

clean:
	@rm -f $(OFILES) $(BOFILES)
	@echo "$(YELLOW)Cleaning object files$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BNAME)
	@echo "$(YELLOW)Cleaning executables$(RESET)"

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./ignore_readline.supp -s ./$(NAME)

re: fclean all

re_bonus : fclean bonus

.PHONY: all bonus clean fclean re
