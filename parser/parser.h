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

# include "libsn/libsn.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>

typedef enum e_token_type
{
	T_LEFT_PAREN,
	T_RIGHT_PAREN,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_REDIRECT_OUT_APPEND,
	T_HEREDOC,
	T_STRING_SINGLE,
	T_STRING_DOUBLE,
	T_PIPE,
	T_OR,
	T_AND,
	T_WILDCARD,
	T_BLANK,
	T_WORD,
	T_VAR,
	T_SKIPPABLE,
	T_EOF,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;


typedef struct s_cmd t_cmd;

typedef struct s_basic_cmd
{
	char *name;
	char *args[];
} t_basic_cmd;

typedef struct s_redirect
{
	char *type;
	char *file;
	t_basic_cmd *cmd;
} t_redirect;

typedef struct s_pipe
{
	t_basic_cmd *left;
	t_cmd *right;
} t_pipe;


typedef enum e_cmd_type
{
	C_CMD,
	C_PIPE,
	C_REDIRECT,
} t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type			type;
	union
	{
		t_basic_cmd cmd;
		t_pipe pipe;
	} u_as;
}						t_expr;

t_token				*token_new(t_token_type type, char *lexeme);
void				token_free(t_token *token);
void				tokens_free(t_token *token);
void				token_str(t_token *t, bool nl, bool all);
const char			*token_type_str(t_token_type type);
t_token				*tokens_scan(char *src);

bool				is_metachar(char *src, size_t current);
bool				is_name(char *src, size_t current);
bool				match_char(char *src, size_t *current, char expected);
bool				match_word(char *src, size_t *current);
bool				match_identifier(char *src, size_t *current);
bool				match_var(char *src, size_t *current);
char				*extract_word(char *src, size_t *current);
t_token				*token_identify(char *src, size_t *current);
t_token				*extract_str(char *src, size_t *current, bool single);
t_token				*extract_identifier(char *src, size_t *current);
t_token				*extract_var(char *src, size_t *current);
t_token				*extract_blank(char *src, size_t *current);

int					exec_cmd(char *program, char *args[], char *envp[]);

#endif
