/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:13:08 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/15 16:07:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_test_header(void)
{
	ft_printf("\n  -------------------TEST RESULTS-------------------\n");
}

void	print_test_separator(int print_on)
{
	if (print_on)
		ft_printf("  --------------------------------------------------\n");
}

void	print_test_result(t_list *node)
{
	t_result	*result;
	int			total;

	result = node->data;
	total = result->success + result->failure + result->segv + result->segbus;
	ft_printf("%-20s > [%@s: %2d][%@s: %2d][%@s: %2d]"
			, result->name
			, BLUE, "TOTAL", total
			, GREEN, "OK", result->success
			, RED, "KO", result->failure);
	if (result->segv)
		ft_printf("[%@s: %2d]", RED, "SEGV", result->segv);
	if (result->segbus)
		ft_printf("[%@s: %2d]", RED, "ABRT", result->segbus);
	ft_putchar('\n');
}

void	print_test_summary(t_list *summary)
{
	t_result *result;

	result = summary->data;
	ft_printf("%s >> OK : %d | KO : %d"
			, result->name, result->success, result->failure);
}
