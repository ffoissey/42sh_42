/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:34:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static uint8_t	check_cmd_path(char *data)
{
	struct stat	stat;

	if (lstat(data, &stat))
	{
		ft_dprintf(2, "42sh: %s: no such file or directory\n", data);
		return (FALSE);
	}
	if (stat.st_mode & S_IFDIR)
		ft_dprintf(2, "42sh: %s: Is a directory\n", data);
	else if (access(data, X_OK))
		ft_dprintf(2, "42sh: %s: Permission denied\n", data);
	else
		return (TRUE);
	return (FALSE);
}

static int8_t	run_child(t_process *process, char **env)
{
	char		*pathname;

	pathname = NULL;
	if (process->type & IS_BIN)
	{
		pathname = ft_hmap_getdata(&g_shell->hash.bin, process->av[0]);
		if (check_cmd_path(pathname) != TRUE)
			pathname = NULL;
	}
	else if (process->type & IS_ABS)
	{
		if (check_cmd_path(process->av[0]) == TRUE)
			pathname = process->av[0];
	}
	else if (process->type & IS_NOTFOUND)
		ft_dprintf(2, "42sh: %s: command not found\n", process->av[0]);
	if (pathname != NULL)
	{
		if (execve(pathname, process->av, env) == FAILURE)
			ft_dprintf(2, "42sh: execution error\n");
	}
	exit(1);
	return (FAILURE);
}

static int8_t	child_process(t_process *process, char **env, uint8_t fg)
{
	process->pid = getpid();
	if (*process->pgid == 0)
		*process->pgid = process->pid;
	setpgid(process->pid, *process->pgid);
	if (fg == TRUE)
		tcsetpgrp(STDIN_FILENO, *process->pgid);
	if (setup_redirect(process) == FAILURE)
		exit(1);
	init_exec_signals();
	if (process->type & IS_BLT)
	{
		run_builtin(process, fg);
		exit(process->status);
	}
	else
		return (run_child(process, env));
}

static int8_t	parent_process(t_process *process, char ***env, uint8_t fg)
{
	if (process->type & IS_BIN)
		ft_hmap_hits(&g_shell->hash.bin, process->av[0]);
	if (*process->pgid == 0)
		*process->pgid = process->pid;
	setpgid(process->pid, *process->pgid);
	if (fg == TRUE)
		tcsetpgrp(STDIN_FILENO, *process->pgid);
	ft_freetab(env);
	return (SUCCESS);
}

int8_t			fork_process(t_process *process, uint8_t foreground)
{
	char			**env;

	if ((env = generate_env(g_shell, process->env)) == NULL)
	{
		process->type |= IS_EXP_ERROR;
		return (FAILURE);
	}
	if (ft_strequ(get_var(process->env, "PATH")
				, get_var(g_shell->intern, "PATH")) == FALSE)
	{
		process->type = 0;
		get_process_type(process->env, process);
	}
	if ((process->pid = fork()) < 0)
	{
		ft_freetab(&env);
		ft_dprintf(2, "42sh: fork error\n");
		return (FAILURE);
	}
	else if (process->pid == 0)
		return (child_process(process, env, foreground));
	else
		return (parent_process(process, &env, foreground));
}
