/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

bool	is_metachar_bonus(char *src, size_t current, bool is_quoted)
{
	if (src[current] == '\'' || src[current] == '"')
		return (true);
	if (src[current] == '$' && is_name(src, current + 1))
		return (true);
	if (!is_quoted && (src[current] == ' ' || src[current] == '\t'
			|| src[current] == '\n'))
		return (true);
	if (!is_quoted && src[current] == '|')
		return (true);
	if (!is_quoted && (src[current] == '<' || src[current] == '>'))
		return (true);
	return (false);
}
