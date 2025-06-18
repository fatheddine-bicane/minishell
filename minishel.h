/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:36:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 22:01:30 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include "./my_library/my_library.h"
# include <errno.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/stat.h>
# include "./parser/parser.h"

// INFO: std_files marcors
/*-----------------------------------------------*/
# ifndef SAVE
#  define SAVE 1
# endif
# ifndef RESTORE_BOTH
#  define RESTORE_BOTH 2
# endif
# ifndef RESTORE_STDIN
#  define RESTORE_STDIN 3
# endif
# ifndef RESTORE_STDOUT
#  define RESTORE_STDOUT 4
# endif
/*-----------------------------------------------*/

// INFO: colors
/*-----------------------------------------------*/
# ifndef BLUE
#  define BLUE  "\001\033[34m\002"
# endif
# ifndef GREEN
#  define GREEN "\001\033[32m\002"
# endif
# ifndef RED
#  define RED   "\001\033[31m\002"
# endif
# ifndef YELLOW
#  define YELLOW "\001\033[0;33m\002"
# endif
# ifndef RESET
#  define RESET "\001\033[0m\002"
# endif
/*-----------------------------------------------*/

extern volatile sig_atomic_t	g_signal_flag;

typedef enum e_exp_flags
{
	EXP_IS_DLIMITER = 1 << 0,
	EXP_IS_BODY = 1 << 1,
	EXP_IS_QUOTED = 1 << 2,
}			t_exp_flags;

typedef struct s_wait_pids		t_wait_pids;
typedef struct s_pipex			t_pipex;

// INFO: shell main
/*-----------------------------------------------*/
typedef struct s_shell
{
	t_cmd			*cmd;
	t_cmd			*root_to_free;
	int				exit_status;
	t_list			*my_envp;
	t_pipex			*pipex;
	t_wait_pids		*pids;
	char			**heredocs_files;
	char			**heredocs_delemiters;
	int				herdocs_index;
	bool			redirections_status;
	bool			is_pipe;
	bool			is_group;
	t_str_builder	*sb_to_free;
	char			*rl;
	char			*prompt;
	int				ast_status;
}	t_shell;

void	run_ast(t_shell *shell);
int		clean_shell(t_shell *shell);
bool	rl_faild(t_shell *shell);
/*-----------------------------------------------*/

// INFO: costume prompt
/*-----------------------------------------------*/
typedef struct s_prompt
{
	char	path[PATH_MAX];
	char	*prompt;
	char	*to_free;
	char	*exit_stat;
	char	*cwd;
	int		slash_count;
	int		i;
}	t_prompt;

char	*custum_prompt(t_shell *shell);
void	change_pwd_protections(t_shell *shell);
/*-----------------------------------------------*/

// NOTE: builtins
/*-----------------------------------------------------------------*/

// NOTE: unset builtin
typedef struct s_unset
{
	t_list	*env_to_del;
	t_list	*tmp_envp;
	char	*env_cont;
	int		i;
	int		v_i;
	bool	skip_loop;
}	t_unset;
void	ft_unset(t_shell *shell);
// NOTE: cd builtin
typedef struct s_cd
{
	char	*home_path;
	char	*oldpwd;
	t_shell	*shell;
}	t_cd;
void	ft_cd(t_shell *shell);
void	cd_error(t_cd *cd, int error_mssg);
void	change_pwd(t_shell *shell);
bool	protect_cwd_cd(t_shell *shell);
void	change_pwd_utils(t_list **tmp, char *path);
// INFO: export builtin
void	ft_export(t_shell *shell);
void	ft_export_utils_1(t_shell *shell, char *variable);
void	export_error(t_shell *shell, int *vars_i);
// NOTE: exit builtin
void	ft_exit(t_shell *shell);
void	exit_error(t_shell *shell, int error_mssg);
// NOTE: echo builtin
void	ft_echo(t_shell *shell);
// INFO: env builtin
void	ft_env(t_shell *shell);
// INFO: pwd builtin
void	ft_pwd(t_shell *shell);
/*-----------------------------------------------------------------*/

// INFO: executables (ls, clear, grep, ...)
/*---------------------------------------------------------------*/
typedef struct s_executable
{
	char	**paths;
	char	**com;
	char	**penvp;
	char	*path;
	int		i;
}	t_executable;

void	ft_apply_comm(t_shell *shell, bool to_fork, pid_t pid_r);
void	ft_executable(t_shell *shell, pid_t pid, bool to_wait);
void	command_is_path(pid_t pid, t_shell *shell, bool to_wait);
void	command_is_not_path(pid_t pid, t_shell *shell, bool to_wait);
t_list	*ft_set_env(char **envp);
void	executable_error(t_shell *shell, int error_mssg, char **prep_envp);
void	executable_error_2(t_shell *shell, int error_mssg);
void	executable_error_3(t_shell *shell, t_executable *exec,
			int error_mssg, pid_t pid);
void	executable_error_4(t_shell *shell, t_executable *exec,
			int error_mssg, pid_t pid);
void	executable_error_5(t_shell *shell, int error_mssg);
/*---------------------------------------------------------------*/

// INFO: pipes
/*--------------------------------------------*/
typedef struct s_wait_pids
{
	pid_t				pid;
	struct s_wait_pids	*next;
}	t_wait_pids;

typedef struct s_pipex
{
	t_cmd			*cmd;
	struct s_pipex	*next;
}	t_pipex;

typedef struct s_pipes
{
	t_pipex		*pipex_to_free;
	t_pipex		*pipex;
	pid_t		pid;
	int			prev_pipe[2];
	int			fd[2];
	t_wait_pids	*pids;
}	t_pipes;

bool	ft_is_builtin(char *command);
void	run_bultins(t_shell *shell);
void	ft_exec_builtins(char **command_arg, t_list **my_envp, int *exit_stat);
void	pipe_error(t_shell *shell, int error_mssg, char **prep_envp);
void	pipe_error_2(t_shell *shell, int error_mssg,
			t_executable *executable_error);
void	pipe_error_3(t_shell *shell, t_executable *executable,
			int error_mssg, pid_t pid);
void	add_pid(t_wait_pids **pids, pid_t pid);
void	free_pids(t_wait_pids **pids);
void	wait_pids(t_wait_pids **pids, t_shell *shell);
void	free_pipex(t_pipex **pipex);
void	creat_pipex(t_cmd *cmd, t_pipex **pipex);
void	increment_heredoc_pipe(t_shell *shell, t_pipex *tmp);
void	pipes_child_utils(t_pipes *pipes, t_shell *shell);
char	**ft_prep_envp(t_shell *shell); //INFO: transform the envp to char **
void	ft_pipex(char **commands, t_list **my_envp,
			int *exit_stat); //INFO: handle pipes
/*--------------------------------------------*/

// INFO: herdocs
/*--------------------------------------------*/
typedef struct s_create_heredoc
{
	char	*input;
	char	*file_name;
	int		inf;
}	t_create_heredoc;

typedef struct s_randome_name
{
	char	*file_name;
	char	*file_name_m;
	char	*tmp_path;
	int		random_file;
	char	path[PATH_MAX];
}	t_randome_name;

void	ft_here_doc(char *rl);
char	*creat_here_doc(char *delimiter, t_shell *shell);
char	*ft_creat_input(char *limiter, t_shell *shell);
char	*random_name(void);
bool	here_doc(t_shell *shell);
char	*expand_heredoc_delimiter(char *src, t_shell *shell);
bool	has_quote(char *src);
char	*expand_heredoc_body(char *src, t_shell *shell, bool is_quoted);
bool	handle_herdocs(t_shell *shell);
void	ft_here_doc(char *delimiter); //INFO: creat here_doc input
void	herdocs_delemiters(t_shell *shell);
void	increment_heredoc_index(t_shell *shell, t_cmd *cmd);
/*--------------------------------------------*/

// INFO: redirections
/*--------------------------------------------*/
bool	redirect_input(char *file_name);
bool	redirect_output(char *file_name);
bool	appent_output(char *file_name);
bool	handle_redirections(char **redirections, t_shell *shell);
void	is_redirection(t_shell *shell, bool to_fork, pid_t pid_r);
void	std_files(int what_to_do);
/*--------------------------------------------*/

// INFO: group
/*--------------------------------------------*/
void	is_group(t_shell *shell);
void	creat_heredoc_group(t_shell *shell, t_str_builder **sb);
/*--------------------------------------------*/

// INFO: compound
/*--------------------------------------------*/
void	is_compound(t_shell *shell);
/*--------------------------------------------*/

// INFO: setting costume envp struct
/*--------------------------------------------*/
typedef struct s_set_envp
{
	t_list	*my_envp;
	int		i;
	char	*shlvl_var;
	int		lvl;
}	t_set_envp;
/*--------------------------------------------*/

// INFO: free fucntions
/*--------------------------------------------*/
void	free_my_envp(t_list **my_envp);
void	ft_free_arr(char **arr_s);
/*--------------------------------------------*/

// INFO: parcing merged code
/*-----------------------------------------------------------*/
void	is_command(t_shell *shell, bool to_fork, pid_t pid_r);
void	is_pipe(t_shell *shell);
char	*get_ifs_var(t_list *envp);
char	**ft_split_variable(char *variable);
bool	expand_params(char ***args, t_shell *shell);
char	*expand_single_param(char *src, t_shell *shell);
/*-----------------------------------------------------------*/

// INFO: signals
/*--------------------------------------------*/
void	setup_signals(void);
void	ignore_signals_parrent(void);
void	wait_child(pid_t pid, t_shell *shell);
void	setup_signals_child(void);
void	setup_signals_heredoc(void);
/*--------------------------------------------*/

// INFO: error struct
/*--------------------------------------------*/
typedef struct s_error
{
	t_shell			*shell;
	t_executable	*exec;
	int				error_mssg;
	pid_t			pid;
	char			**prep_envp;
}	t_error;
/*--------------------------------------------*/

#endif
