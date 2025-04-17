/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:36:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/12 16:10:45 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
#define MINISHEL_H

# include "./my_library/my_library.h"
# include <errno.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

typedef struct s_array
{
	unsigned int	len;
	unsigned int	capacity;
	char			**array;
}	t_array;


void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_echo(bool _n, char **arr);
void	ft_exit(void);
void	ft_export(char **envp);
char	**ft_unset(char **envp, char *variable);

bool	ft_check_env(t_array *my_envp, char *variable);


char	**ft_set_my_envp(char **envp);

t_array	*ft_set_env_(char **envp);
t_array	*ft_init_arr(void);
t_array	*ft_resize(t_array **array);


#endif
