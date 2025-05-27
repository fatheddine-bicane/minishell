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
	char	*name;

	name = "exec";
	got = ast_gen("ls -al -h");
	want = "(exec ls -al -h)";
	if (sn_strncmp(got, want, sn_strlen(want)) != 0)
	{
		sn_eprintf("test %s(KO!): wanted `%s`; got `%s`\n", name, want, got);
		return (free(got), EXIT_FAILURE);
	}
	else
		sn_printf("test %s(OK!)\n", name);
	return (free(got), EXIT_SUCCESS);
}

int	test_exec_no_cmd(void)
{
	char	*got;
	char	*want;
	char	*name;

	name = "exec_no_cmd";
	got = ast_gen("");
	want = "empty";
	if (sn_strncmp(got, want, sn_strlen(want)) != 0)
	{
		sn_eprintf("test %s(KO!): wanted `%s`; got `%s`\n", name, want, got);
		return (free(got), EXIT_FAILURE);
	}
	else
		sn_printf("test %s(OK!)\n", name);
	return (free(got), EXIT_SUCCESS);
}

int	test_exec_redirect_with_no_cmd(void)
{
	char	*got;
	char	*want;
	char	*name;

	name = "exec_redirect_with_no_cmd";
	got = ast_gen("> file");
	want = "(redirect > file)";
	if (sn_strncmp(got, want, sn_strlen(want)) != 0)
	{
		sn_eprintf("test %s(KO!): wanted `%s`; got `%s`\n", name, want, got);
		return (free(got), EXIT_FAILURE);
	}
	else
		sn_printf("test %s(OK!)\n", name);
	return (free(got), EXIT_SUCCESS);
}

int	test_exec_right_redirection(void)
{
	char	*got;
	char	*want;
	char	*name;

	name = "exec_right_redirection";
	got = ast_gen("ls -al > file -h");
	want = "(redirect > file (exec ls -al -h)";
	if (sn_strncmp(got, want, sn_strlen(want)) != 0)
	{
		sn_eprintf("test %s(KO!): wanted `%s`; got `%s`\n", name, want, got);
		return (free(got), EXIT_FAILURE);
	}
	else
		sn_printf("test %s(OK!)\n", name);
	return (free(got), EXIT_SUCCESS);
}

int	test_exec_mixed_redirection(void)
{
	char	*got;
	char	*want;
	char	*name;

	name = "exec_mixed_redirection";
	got = ast_gen("cat > file -e < file2 -b >> text.txt << heredoc");
	want = "(redirect > file (redirect < file2 (redirect >> text.txt (redirect << heredoc (exec cat\
 -e -b))))";
	if (sn_strncmp(got, want, sn_strlen(want)) != 0)
	{
		sn_eprintf("test %s(KO!): wanted `%s`; got `%s`\n", name, want, got);
		return (free(got), EXIT_FAILURE);
	}
	else
		sn_printf("test %s(OK!)\n", name);
	return (free(got), EXIT_SUCCESS);
}
