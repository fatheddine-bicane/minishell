/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <unistd.h>

typedef struct s_str_builder
{
	char				**buff;
	size_t				cap;
	size_t				len;
	size_t				total_size;
}						t_str_builder;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef EXIT_SYNTAX_ERROR
#  define EXIT_SYNTAX_ERROR 2
# endif //  EXIT_SYNTAX_ERROR

# ifndef RED
#  define RED "\001\033[31m\002"
# endif

# ifndef RESET
#  define RESET "\001\033[0m\002"
# endif

# ifndef EXIT_EMPTY_AST
#  define EXIT_EMPTY_AST 3
# endif //  EXIT_EMPTY_AST

typedef enum e_token_type
{
	T_LEFT_PAREN,
	T_RIGHT_PAREN,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_OUT_APPEND,
	T_HEREDOC,
	T_STR_SINGLE,
	T_STR_DOUBLE,
	T_PIPE,
	T_OR,
	T_AND,
	T_WILDCARD,
	T_BLANK,
	T_WORD,
	T_VAR,
	T_SKIPPABLE,
	T_EOF,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*lexeme;
	char				*str;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_cmd	t_cmd;

typedef struct s_exec
{
	char				**argv;
}						t_exec;

typedef struct s_redirect
{
	int					type;
	char				*file;
	t_cmd				*next;
}						t_redirect;

typedef struct s_pipe
{
	t_cmd				*left;
	t_cmd				*right;
}						t_pipe;

typedef struct s_compound_cmd
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_compound;

typedef struct s_group
{
	t_cmd				*cmd;
}						t_group;

typedef enum e_cmd_type
{
	C_EXEC,
	C_PIPE,
	C_REDIRECT,
	C_GROUP,
	C_COMPOUND,
}						t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type			type;
	t_cmd				*parent;
	union
	{
		t_exec			exec;
		t_redirect		redirect;
		t_pipe			pipe;
		t_compound		compound;
		t_group			group;
	} u_as;
}						t_cmd;

int						sn_atoi(const char *nptr, int *valid);
int						sn_isdigit(int c);
int						sn_isalpha(int c);
int						sn_isalphanum(int c);
size_t					sn_strlen(const char *s);
void					*sn_calloc(size_t nmemb, size_t size);
void					sn_bzero(void *s, size_t n);
void					*sn_memset(void *s, int c, size_t n);
void					*sn_memcpy(void *dest, const void *src, size_t n);
void					*sn_memmove(void *dest, const void *src, size_t n);
char					*sn_strdup(const char *s);
size_t					sn_strlcpy(char *dst, const char *src, size_t size);
char					*sn_substr(char const *s, unsigned int start,
							size_t len);
int						sn_strncmp(const char *s1, const char *s2, size_t n);
char					**sn_split(char const *s, char c);
char					*sn_strjoin(char *start, char *end, char join);
char					*sn_strsearch(char *haystack[], char *needle);
void					sn_strs_free(char **arr);
char					*sn_strndup(const char *src, size_t n);
char					*sn_readfile(char *file);

int						sn_vprintf_fd(va_list args, int fd, const char *format,
							...);
int						sn_printf(const char *format, ...);
int						sn_eprintf(const char *format, ...);
int						sn_vprintf(va_list args, const char *format, ...);
int						sn_printf_fd(int fd, const char *format, ...);
int						sn_sprintf(char **buff, const char *format, ...);
int						sn_vsprintf(va_list args, char **buff, const char *s,
							...);
int						sn_print_parse(va_list ap, t_str_builder *sb,
							const char *s, size_t *i);
char					*sn_strchr(const char *s, int c);
int						sn_putstr_fd(char *str, int fd);
int						sn_putchr(char c);
int						sn_putchr_fd(char c, int fd);
int						sn_putstr(char *s);
int						sn_putnbr(int n, int fd);
int						sn_putunbr(unsigned int n, int fd);
int						sn_putnbr_hex(unsigned long num, int uppercase, int fd);
int						sn_putptr(void *num, int fd);

ssize_t					sn_istrchr(const char *s, char c);

t_str_builder			*sb_create(size_t cap);
void					sb_free(t_str_builder *sb);
bool					sb_ensure_size(t_str_builder *sb, size_t len);
void					sb_truncate(t_str_builder *sb, size_t len);
void					sb_clear(t_str_builder *sb);
void					sb_drop(t_str_builder *sb, size_t len);

char					**sb_split(t_str_builder *sb, char c);
bool					sb_append_str(t_str_builder *sb, const char *str,
							size_t len);
bool					sb_append_char(t_str_builder *sb, char c);
bool					sb_append_nbr(t_str_builder *sb, int n);
bool					sb_append_unbr(t_str_builder *sb, unsigned int n);
bool					sb_append_ptr(t_str_builder *sb, void *ptr);
bool					sb_append_hex(t_str_builder *sb, unsigned long num,
							int uppercase);
size_t					sb_len(t_str_builder *sb);
size_t					sb_total_size(t_str_builder *sb);
const char				*sb_str(t_str_builder *sb, size_t index);
char					**sb_build(t_str_builder *sb);
char					*sb_build_str(t_str_builder *sb);
char					*sb_str_at(t_str_builder *sb, size_t i);

t_token					*token_new(t_token_type type, char *lexeme);
void					token_free(t_token *token);
void					tokens_free(t_token *token);
void					token_str(t_token *t, bool nl, bool all);
const char				*token_type_str(t_token_type type);
t_token					*tokens_scan(char *src, char **err_msg);
t_token					*tokens_scan_bonus(char *src, char **err_msg);

bool					is_metachar(char *src, size_t current, bool is_quoted);
bool					is_metachar_bonus(char *src, size_t current,
							bool is_quoted);
bool					is_name(char *src, size_t current);
bool					is_end(t_token *token);
bool					is_quote(char *src, size_t current);
bool					is_redirect(t_token *token);
bool					match_char(char *src, size_t *current, char expected);
bool					match_word(char *src, size_t *current, bool is_quoted);
bool					match_word_bonus(char *src, size_t *current,
							bool is_quoted);
bool					match_identifier(char *src, size_t *current);
bool					match_var(char *src, size_t *current);
bool					match_token(t_token **head, size_t count, ...);
bool					match_tokens(t_token **head, size_t count, ...);
char					*extract_word(char *src, size_t *current);
t_token					*token_identify(char *src, size_t *current,
							char **err_msg);
t_token					*token_identify_bonus(char *src, size_t *current,
							char **err_msg);
t_token					*extract_str(char *src, size_t *current, bool single,
							char **err_msg);
t_token					*extract_identifier(char *src, size_t *current);
t_token					*extract_var(char *src, size_t *current);
t_token					*extract_blank(char *src, size_t *current);

t_cmd					*cmd_exec_init(char **argv, t_cmd *parent);
t_cmd					*cmd_redirect_init(int type, char *file, t_cmd *next,
							t_cmd *parent);
t_cmd					*cmd_pipe_init(t_cmd *left, t_cmd *right,
							t_cmd *parent);
t_cmd					*cmd_group_init(t_cmd *group, t_cmd *parent);
t_cmd					*cmd_cmp_init(int op, t_cmd *left, t_cmd *right,
							t_cmd *parent);

int						extract_cmp_op(t_token *token);
char					*extract_lexeme_err(t_token *token);

int						create_ast(char *src, t_cmd **ast);
int						create_ast_bonus(char *src, t_cmd **ast);
void					ast_free(t_cmd *root);
char					*ast_output(t_cmd *cmd, bool print);

#endif
