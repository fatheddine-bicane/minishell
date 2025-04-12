/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:42 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/11 13:25:51 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

t_array	*ft_init_arr(void)
{
	t_array *arr;

	arr = malloc(sizeof(t_array));
	if (NULL == arr)
		return (NULL);
	arr->capacity = 5;
	arr->len = 0;
	arr->array = malloc(sizeof(char *) * 30);
	if (NULL == arr->array)
		return (free(arr), NULL);
	return (arr);
}

static void	ft_free(char **arr_s)
{
	int	i;

	i = 0;
	if (!arr_s)
		return ;
	while (arr_s[i] != 0)
	{
		free(arr_s[i]);
		i++;
	}
	free (arr_s);
}

static void	ft_copy_arr(t_array **original, t_array **resized)
{
	size_t	i;

	i = 0;
	while (i < (*original)->len)
	{
		(*resized)->array[i] = ft_strdup((char *)((*original)->array[i]));
		i++;
	}
	ft_free((*original)->array);
	free((*original));
}

t_array	*ft_resize(t_array **array)
{
	t_array *arr;

	arr = malloc(sizeof(t_array));
	if (NULL == arr)
		return (NULL);
	arr->capacity = (*array)->capacity * 2;
	arr->len = (*array)->len;
	arr->array = malloc(sizeof(char *) * arr->capacity);
	if (NULL == arr->array)
		return (NULL);
	ft_copy_arr(array, &arr);
	return (arr);
}
