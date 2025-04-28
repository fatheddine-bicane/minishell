/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsn.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSN_H
# define LIBSN_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_str_builder
{
	char		*buff;
	size_t		cap;
	size_t		len;
}				t_str_builder;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

int				sn_atoi(const char *nptr, int *valid);
int				sn_isdigit(int c);
int				sn_isalpha(int c);
int				sn_isalphanum(int c);
size_t			sn_strlen(const char *s);
void			*sn_calloc(size_t nmemb, size_t size);
void			sn_bzero(void *s, size_t n);
void			*sn_memset(void *s, int c, size_t n);
void			*sn_memcpy(void *dest, const void *src, size_t n);
void			*sn_memmove(void *dest, const void *src, size_t n);
char			*sn_strdup(const char *s);
size_t			sn_strlcpy(char *dst, const char *src, size_t size);
char			*sn_substr(char const *s, unsigned int start, size_t len);
int				sn_strncmp(const char *s1, const char *s2, size_t n);
char			**sn_split(char const *s, char c);
char			*sn_strjoin(char *start, char *end, char join);
char			*sn_strsearch(char *haystack[], char *needle);
char			**sn_split_free(char **arr);
char			*sn_strndup(const char *src, size_t n);
char			*sn_readfile(char *file);

int				sn_vprintf_fd(va_list args, int fd, const char *format, ...);
int				sn_printf(const char *format, ...);
int				sn_vprintf(va_list args, const char *format, ...);
int				sn_printf_fd(int fd, const char *format, ...);
int				sn_sprintf(char **buff, const char *format, ...);
int				sn_vsprintf(va_list args, char **buff, const char *s, ...);
char			*sn_strchr(const char *s, int c);
int				sn_putstr_fd(char *str, int fd);
int				sn_putchr(char c);
int				sn_putchr_fd(char c, int fd);
int				sn_putstr(char *s);
int				sn_putnbr(int n, int fd);
int				sn_putunbr(unsigned int n, int fd);
int				sn_putnbr_hex(unsigned long num, int uppercase, int fd);
int				sn_putptr(void *num, int fd);

ssize_t			get_next_line(int fd, char **receiver);
ssize_t			sn_istrchr(const char *s, char c);

t_str_builder	*sb_create(size_t cap);
void			sb_free(t_str_builder *sb);
bool			sb_ensure_size(t_str_builder *sb, size_t len);
void			sb_truncate(t_str_builder *sb, size_t len);
void			sb_clear(t_str_builder *sb);
void			sb_drop(t_str_builder *sb, size_t len);
bool			sb_append_str(t_str_builder *sb, const char *str, size_t len);
bool			sb_append_char(t_str_builder *sb, char c);
bool			sb_append_nbr(t_str_builder *sb, int n);
bool			sb_append_unbr(t_str_builder *sb, unsigned int n);
bool			sb_append_ptr(t_str_builder *sb, void *ptr);
bool			sb_append_hex(t_str_builder *sb, unsigned long num,
					int uppercase);
size_t			sb_len(t_str_builder *sb);
const char		*sb_str(t_str_builder *sb);
char			*sb_build(t_str_builder *sb);

#endif
