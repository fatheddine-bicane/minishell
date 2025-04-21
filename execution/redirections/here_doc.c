/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:22:24 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/20 17:22:40 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

/*static char	*ft_apend_new_line(char *str)*/
/*{*/
/*	int		i;*/
/*	char	*str2;*/
/**/
/*	i = 0;*/
/*	str2 = malloc(sizeof(char) * (ft_strlen(str) + 2));*/
/*	while (str[i])*/
/*	{*/
/*		str2[i] = str[i];*/
/*		i++;*/
/*	}*/
/*	str2[i] = '\n';*/
/*	i++;*/
/*	str2[i] = '\0';*/
/*	return (str2);*/
/*}*/
/**/
/*static char	*ft_creat_input(char *limiter)*/
/*{*/
/*	char	*str;*/
/*	char	*join;*/
/*	char	*join_m;*/
/*	char	*limiter_n;*/
/**/
/*	join = ft_strdup("");*/
/*	limiter_n = ft_apend_new_line(limiter);*/
/*	str = get_next_line(0);*/
/*	while (str && ft_strncmp(str, limiter_n, ft_strlen(limiter_n)))*/
/*	{*/
/*		join_m = join;*/
/*		join = ft_strjoin(join, str);*/
/*		free(join_m);*/
/*		free(str);*/
/*		str = get_next_line(0);*/
/*	}*/
/*	free(str);*/
/*	get_next_line(-1);*/
/*	free(limiter_n);*/
/*	return (join);*/
/*}*/

void	ft_here_doc(char *rl)
{
	char *str;

	if (!ft_strncmp(rl, "test", 4))
	{
		str = get_next_line(0);
		printf("%s\n", str);
	}
}
