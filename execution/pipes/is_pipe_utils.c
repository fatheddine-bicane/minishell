/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:28:26 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 14:37:42 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

t_wait_pids	*new_pid(pid_t pid)
{
	t_wait_pids	*res;

	res = malloc(sizeof(t_wait_pids));
	if (!res)
		return (NULL);
	res->pid = pid;
	res->next = NULL;
	return (res);
}

void	add_pid(t_wait_pids **pids, pid_t pid)
{
	t_wait_pids	*tmp;

	if (!(*pids))
		(*pids) = new_pid(pid);
	else
	{
		tmp = (*pids);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_pid(pid);
	}
}

void	free_pids(t_wait_pids **pids)
{
	t_wait_pids	*tmp;
	t_wait_pids	*to_free;

	tmp = (*pids);
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
}

void	wait_pids(t_wait_pids **pids, t_shell *shell)
{
	t_wait_pids	*tmp;

	tmp = (*pids);
	while (tmp)
	{
		wait_child(tmp->pid, shell);
		tmp = tmp->next;
	}
	free_pids(pids);
}
