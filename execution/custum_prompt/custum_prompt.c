/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custum_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:28:22 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/09 16:32:35 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	change_pwd_protections(t_shell *shell)
{
	char	*path;
	t_list	*tmp;
	t_list	*my_envp;

	path = ft_strdup("/");
	tmp = shell->my_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PWD=", 4))
		{
			free(tmp->content);
			tmp->content = ft_strjoin("PWD=", path);
			free (path);
			return ;
		}
		tmp = tmp->next;
	}
	my_envp = shell->my_envp;
	if (NULL == tmp)
	{
		ft_lstadd_back(&my_envp, ft_lstnew(ft_strjoin("PWD=", path)));
		free (path);
	}
}

static void	protect_cwd(t_prompt *prompt, t_shell *shell)
{
	prompt->cwd = getcwd(NULL, 0);
	if (!prompt->cwd && errno == ENOENT)
	{
		chdir("/");
		change_pwd_protections(shell);
		ft_printf(RED"getcwd: cannot access parent directories: ");
		ft_printf("No such file or directory\n"RESET);
	}
	free(prompt->cwd);
}

void	non_0_exit_status(t_prompt *prompt, t_shell *shell)
{
	prompt->to_free = prompt->prompt;
	prompt->prompt = ft_strjoin(prompt->prompt, RED " [");
	free(prompt->to_free);
	prompt->exit_stat = ft_itoa(shell->exit_status);
	prompt->to_free = prompt->prompt;
	prompt->prompt = ft_strjoin(prompt->prompt, prompt->exit_stat);
	free(prompt->to_free);
	free(prompt->exit_stat);
	prompt->to_free = prompt->prompt;
	prompt->prompt = ft_strjoin(prompt->prompt, "✘]>> " RESET);
	free(prompt->to_free);
}

void	set_folder_path(t_prompt *prompt)
{
	prompt->prompt = ft_strjoin(BLUE " [ ~/", prompt->path + prompt->i);
	prompt->to_free = prompt->prompt;
	prompt->prompt = ft_strjoin(prompt->prompt, "]");
	free(prompt->to_free);
	prompt->to_free = prompt->prompt;
	prompt->prompt = ft_strjoin(prompt->prompt, RESET);
	free(prompt->to_free);
	prompt->to_free = prompt->prompt;
}

char	*custum_prompt(t_shell *shell)
{
	t_prompt	prompt;

	protect_cwd(&prompt, shell);
	getcwd(prompt.path, sizeof(prompt.path));
	prompt.i = 0;
	prompt.slash_count = 3;
	while (prompt.path[prompt.i])
	{
		if (0 == prompt.slash_count)
			break ;
		if (prompt.path[prompt.i] && '/' == prompt.path[prompt.i])
			prompt.slash_count--;
		prompt.i++;
	}
	set_folder_path(&prompt);
	if (shell->exit_status == 0)
	{
		prompt.to_free = prompt.prompt;
		prompt.prompt = ft_strjoin(prompt.prompt, GREEN " [✔]>> " RESET);
		free(prompt.to_free);
	}
	else
		non_0_exit_status(&prompt, shell);
	return (prompt.prompt);
}
