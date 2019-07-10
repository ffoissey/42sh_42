/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:33:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

void	default_io(char *tty_name)
{
	int		fd;

	fd = open(tty_name, O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	if (fd >= 3)
		close(fd);
	return ;
}

int		set_process_pgid(void *context, void *data)
{
	t_job		*job;
	t_process	*process;

	job = context;
	job->pgid = 0;
	process = data;
	process->pgid = &job->pgid;
	return (SUCCESS);
}
