/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*ast_gen(char *src);

int	test_exec(void)
{
	char	*got;
	char	*want;

	got = ast_gen("ls -al -h");
	want = "(exec ls -al -h)";
	if (sn_strncmp(got, want, sn_strlen(want)) != 0)
	{
		sn_eprintf("test KO!: wanted `%s`; got `%s`\n", want, got);
		return (free(got), EXIT_FAILURE);
	}
	else
		sn_printf("test OK!: exec\n");
	return (free(got), EXIT_SUCCESS);
}
