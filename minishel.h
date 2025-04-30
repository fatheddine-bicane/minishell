/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:36:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/30 11:43:13 by fbicane          ###   ########.fr       */
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
#include <sys/wait.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

// INFO: builtin command
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(t_list *my_envp);
void	ft_echo(char *rl, t_list *my_envp);
void	ft_exit(void);
void	ft_export(char **envp);
void	ft_unset(t_list **my_envp, char *variable);

t_list *ft_set_env(char **envp); //INFO: creat custum envp

void	ft_apply_comm(char *rl, t_list *my_envp); //INFO: apply commands
void	ft_here_doc(char *rl);

int	ft_check_bultins(char *rl, t_list **my_envp);
void	ft_free_arr(char **arr_s);

char **ft_prep_envp(t_list *my_envp); //INFO: transform the envp to char **

void	ft_pipex(char **commands, t_list *my_envp); //INFO: handle pipes
bool	ft_is_builtin(char *command);

void	ft_here_doc(char *rl); //INFO: creat here_doc input

#endif
