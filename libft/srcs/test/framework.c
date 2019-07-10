/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framework.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 05:38:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 08:14:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_malloc.h"

static void		signal_catch(int signal)
{
	if (WTERMSIG(signal) == SIGSEGV)
		ft_dprintf(2, "%@s\n", RED, "[SEGV]", ++g_test_results.segv);
	if (WTERMSIG(signal) == SIGBUS)
		ft_dprintf(2, "%@s\n", RED, "[BUSE]", ++g_test_results.segbus);
	if (WTERMSIG(signal) == SIGABRT)
		ft_dprintf(2, "%@s\n", RED, "[ABRT]", ++g_test_results.sigabort);
	if (WTERMSIG(signal) == SIGILL)
		ft_dprintf(2, "%@s\n", RED, "[SILL]", ++g_test_results.sigkill);
	if (WTERMSIG(signal) == SIGFPE)
		ft_dprintf(2, "%@s\n", RED, "[FPEX]", ++g_test_results.sigfpe);
	exit(3);
}

static void		init_signal_catcher(void)
{
	if (signal(SIGBUS, signal_catch) == SIG_ERR)
		ft_dprintf(2, "Error occured catching the SIGBUS.");
	if (signal(SIGSEGV, signal_catch) == SIG_ERR)
		ft_dprintf(2, "Error occured catching the SIGSEGV.");
	if (signal(SIGABRT, signal_catch) == SIG_ERR)
		ft_dprintf(2, "Error occured catching the SIGSEGV.");
	if (signal(SIGILL, signal_catch) == SIG_ERR)
		ft_dprintf(2, "Error occured catching the SIGSEGV.");
	if (signal(SIGFPE, signal_catch) == SIG_ERR)
		ft_dprintf(2, "Error occured catching the SIGSEGV.");
}

static void		parent_manager(int print_on)
{
	int		checker;

	wait(&checker);
	if (WIFEXITED(checker))
	{
		if (WEXITSTATUS(checker) == EXIT_SUCCESS)
		{
			if (print_on)
				ft_printf("%@s\n", GREEN, "[OK]");
			++g_test_results.success;
		}
		else if (WEXITSTATUS(checker) == EXIT_FAILURE)
		{
			if (print_on)
				ft_dprintf(2, "%@s\n", RED, "[KO]");
			++g_test_results.failure;
		}
	}
	else if (WIFSIGNALED(checker))
		ft_dprintf(2, "%@s\n", RED, "Sig not handled");
}

int				load_test(t_stack *head, char *name, int (*f)(void))
{
	t_test	tmp;

	tmp.name = ft_strdup(name);
	tmp.test = f;
	return (ft_stckpush(head, &tmp, sizeof(t_test)));
}

t_result		run_test(t_stack *tests, char *name, int print_on)
{
	t_test		*to_test;
	pid_t		process;
	int			checker;

	ft_bzero(&g_test_results, sizeof(t_result));
	g_test_results.name = name;
	init_signal_catcher();
	while (tests->size)
	{
		to_test = (t_test *)ft_stckpop(tests);
		if ((process = fork()))
			parent_manager(print_on);
		else
		{
			if (print_on)
				ft_printf("> %-35s: ", to_test->name);
			checker = to_test->test();
			ft_strdel(&to_test->name);
			free(to_test);
			checker ? exit(EXIT_FAILURE) : exit(EXIT_SUCCESS);
		}
	}
	return (g_test_results);
}
