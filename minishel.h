/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:36:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/13 16:43:58 by fbicane          ###   ########.fr       */
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

// INFO: unset struct
typedef struct s_unset
{
	t_list	*env_to_del;
	t_list	*tmp_envp;
	char	*env_cont;
	int		i;
	int		v_i; // INFO: variables index
	bool	skip_loop;
}	t_unset;

// INFO: builtin command
void	ft_cd(char *path, t_list **my_envp);
void	ft_pwd(void);
void	ft_env(t_list *my_envp);
void	ft_echo(char **echo_arg, t_list *my_envp);
void	ft_exit(void);
void	ft_export(t_list **my_envp, char **variables);
void	ft_unset(t_list **my_envp, char **variables);

t_list *ft_set_env(char **envp); //INFO: creat custum envp

void	ft_executable(char *command, t_list *my_envp, pid_t pid, bool to_wait); //INFO: apply commands
void	ft_apply_comm(char *rl, t_list *my_envp);
void	ft_here_doc(char *rl);

int	ft_check_bultins(char *rl, t_list **my_envp);
void	ft_free_arr(char **arr_s);

char **ft_prep_envp(t_list *my_envp); //INFO: transform the envp to char **

void	ft_pipex(char **commands, t_list **my_envp); //INFO: handle pipes
bool	ft_is_builtin(char *command);
void	ft_exec_builtins(char **command_arg, t_list **my_envp);

void	ft_here_doc(char *rl); //INFO: creat here_doc input

#endif
