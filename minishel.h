/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:36:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 21:41:39 by fbicane          ###   ########.fr       */
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

void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(t_list *my_envp);
void	ft_echo(char *rl);
void	ft_exit(void);

void	ft_export(char **envp);
char	**ft_unset(char **envp, char *variable);

t_list *ft_set_env(char **envp);


void	ft_check_bultins(char *rl, t_list **my_envp);
void	ft_free_arr(char **arr_s);

#endif
