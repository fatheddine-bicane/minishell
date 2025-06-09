/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	test_exec(void);
int	test_exec_right_redirection(void);
int	test_exec_mixed_redirection(void);
int	test_exec_no_cmd(void);
int	test_exec_redirect_with_no_cmd(void);

int	main(void)
{
	test_exec();
	test_exec_no_cmd();
	test_exec_redirect_with_no_cmd();
	test_exec_right_redirection();
	test_exec_mixed_redirection();
	return (EXIT_SUCCESS);
}
