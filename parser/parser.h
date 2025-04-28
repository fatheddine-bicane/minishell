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
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sysexits.h>

typedef enum e_token_type
{
	T_LEFT_PAREN,
	T_RIGHT_PAREN,
	T_EQUAL,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_REDIRECT_OUT_APPEND,
	T_HEREDOC,
	T_HEREDOC_DELIMITER,
	T_STRING_SINGLE,
	T_STRING_DOUBLE,
	T_PIPE,
	T_AND,
	T_OR,
	T_IDENTIFIER,
	T_CMD,
	T_VAR,
	T_VAR_VALUE,
	T_VAR_STATUS,
	T_WILDCARD,
	T_SKIPPABLE,
	T_EOF,
	T_UNKNOWN
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

t_token				*token_new(t_token_type type, char *lexeme);
void				token_free(t_token *token);
void				tokens_free(t_token *token);
void				token_str(t_token *t, bool nl, bool all);
const char			*token_type_str(t_token_type type);
t_token				*tokens_scan(char *src);

#endif
