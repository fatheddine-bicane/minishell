/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:36:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/01 21:44:56 by fbicane          ###   ########.fr       */
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
# include <signal.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#include "./parser/parser.h"

# define SAVE 1
# define RESTORE_BOTH 2
# define RESTORE_STDIN 3
# define RESTORE_STDOUT 4

static volatile sig_atomic_t g_signal_flag = 0;

typedef struct s_shell
{
	t_cmd	*cmd;
	t_list	*my_envp;
	int		exit_status;
	bool	redirections_status;
	bool	is_pipe;
}	t_shell;

// NOTE: unset builtin
/*-----------------------------------------------*/
typedef struct s_unset
{
	t_list	*env_to_del;
	t_list	*tmp_envp;
	char	*env_cont;
	int		i;
	int		v_i; // INFO: variables index
	bool	skip_loop;
}	t_unset;

void	ft_unset(t_shell *shell);
/*-----------------------------------------------*/

// NOTE: cd builtin
/*-----------------------------------------------*/
typedef struct s_cd
{
	char	*home_path;
	char	*oldpwd;
	t_shell	*shell;
}	t_cd;

void	ft_cd(t_shell *shell);
void	cd_error(t_cd *cd, int error_mssg);
/*-----------------------------------------------*/

// INFO: export builtin
/*-----------------------------------------------------------------*/
void	ft_export(t_shell *shell);
void	ft_export_utils_1(t_shell *shell, char *variable);
void	export_error(t_shell *shell, int *vars_i);
/*-----------------------------------------------------------------*/

// NOTE: exit builtin
/*-----------------------------------------------------*/
void	ft_exit(t_shell *shell);
void	exit_error(t_shell *shell, int error_mssg);
/*-----------------------------------------------------*/

// NOTE: echo builtin
/*-----------------------------------------------*/
void	ft_echo(t_shell *shell);
/*-----------------------------------------------*/

// INFO: env builtin
/*-----------------------------------------------*/
void	ft_env(t_shell *shell);
/*-----------------------------------------------*/

// INFO: pwd builtin
/*-----------------------------------------------*/
void	ft_pwd(t_shell *shell);
/*-----------------------------------------------*/

// INFO: executables (ls, clear, grep, ...)
/*---------------------------------------------------------------*/
typedef struct s_executable
{
	char	**paths;
	char	**com;
	char	*path;
	int		i;
}	t_executable;

void	ft_apply_comm(t_shell *shell, bool to_fork, pid_t pid_r);
void	ft_executable(t_shell *shell, pid_t pid, bool to_wait);
void	command_is_path(pid_t pid, t_shell *shell, bool to_wait);
void	command_is_not_path(pid_t pid, t_shell *shell, bool to_wait);
t_list *ft_set_env(char **envp); //INFO: creat custum envp

void	executable_error(t_shell *shell, int error_mssg, char **prep_envp);
void	executable_error_2(t_shell *shell, t_executable *executable, int error_mssg);
void	executable_error_3(t_shell *shell, t_executable *executable, int error_mssg, pid_t pid);
/*---------------------------------------------------------------*/




// INFO: free fucntions
/*--------------------------------------------*/
void	free_my_envp(t_list **my_envp);
void	ft_free_arr(char **arr_s);
/*--------------------------------------------*/



// INFO: pipes

typedef struct s_wait_pids
{
	pid_t				pid;
	struct s_wait_pids	*next;
}	t_wait_pids;

void	pipe_error(t_shell *shell, int error_mssg, char **prep_envp);
void	pipe_error_2(t_shell *shell, int error_mssg, t_executable *executable_error);
void	pipe_error_3(t_shell *shell, t_executable *executable, int error_mssg, pid_t pid);
void	add_pid(t_wait_pids **pids, pid_t pid);
void	free_pids(t_wait_pids **pids);
void	wait_pids(t_wait_pids **pids, t_shell *shell);



void	ft_here_doc(char *rl);
bool	here_doc(char **redirections, t_shell *shell, int i);

void	run_bultins(t_shell *shell);




char **ft_prep_envp(t_shell *shell); //INFO: transform the envp to char **
void	ft_pipex(char **commands, t_list **my_envp, int *exit_stat); //INFO: handle pipes
bool	ft_is_builtin(char *command);
void	ft_exec_builtins(char **command_arg, t_list **my_envp, int *exit_stat);

void	ft_here_doc(char *delimiter); //INFO: creat here_doc input


char	**ft_split_variable(char *variable);

bool	handle_redirections(char **redirections, t_shell *shell);

// INFO: signals
void	setup_signals(void);
void	ignore_signals_parrent(void);
void	wait_child(pid_t pid, t_shell *shell);
void	setup_signals_child(void);
void	setup_signals_heredoc(void);


// INFO: parcing merged code
/*void	is_command(t_cmd *cmd, t_list **my_envp, int *exit_stat);*/
void	is_command(t_shell *shell, bool to_fork, pid_t pid_r);
void	is_redirection(t_shell *shell, bool to_fork, pid_t pid_r);
void	std_files(int what_to_do);
/*void	is_pipe(t_cmd *cmd, t_list **my_envp, int *exit_stat, int depth);*/
void	is_pipe(t_shell *shell);

#endif
