/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 04:23:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

static char		*get_histfile(t_registry *shell)
{
	const char	*home;
	char		*histfile;

	home = get_var(shell->intern, "HOME");
	histfile = get_var(shell->intern, "HISTFILE");
	if (histfile != NULL)
		return (ft_strdup(histfile));
	if (home != NULL)
	{
		ft_asprintf(&histfile, "%s/%s",
					home, histfile == NULL ? HISTFILE_DEFAULT : histfile);
		return (histfile);
	}
	return (NULL);
}

static int		get_histfile_fd(t_registry *shell, int flags)
{
	char		*histfile;
	struct stat	st;
	int			fd;

	histfile = get_histfile(shell);
	if (histfile == NULL)
		return (-1);
	fd = open(histfile, flags, S_IRUSR | S_IWUSR);
	if (stat(histfile, &st) != SUCCESS || (st.st_mode & S_IFREG) == FALSE)
	{
		close(fd);
		fd = -1;
	}
	ft_strdel(&histfile);
	return (fd);
}

static int		get_histsize(t_registry *shell)
{
	const char	*tmp;
	int			histsize;

	tmp = get_var(shell->intern, "HISTSIZE");
	if (tmp == NULL)
		histsize = HISTSIZE_DEFAULT;
	else
		histsize = ft_atoi(tmp);
	if (histsize < 128 || histsize > 32768)
		histsize = HISTSIZE_DEFAULT;
	return (histsize);
}

void			read_histfile(t_registry *shell, t_history *history)
{
	char	*cmd;
	int		fd;

	if ((fd = get_histfile_fd(shell, O_CREAT | O_RDONLY)) == FAILURE)
		return ;
	cmd = NULL;
	while (get_next_line(fd, &cmd) > 0)
	{
		if (cmd != NULL)
		{
			if (ft_strcheck(cmd, ft_isprint) == TRUE
					&& *cmd != '\0' && *cmd != '\n')
				add_entry(&history->entry, create_entry(cmd));
			ft_strdel(&cmd);
			history->head_ptr = history->entry;
			history->nb_of_entries++;
		}
	}
	ft_strdel(&cmd);
	close(fd);
}

void			write_histfile(t_registry *shell, t_history *history)
{
	t_entry		*entry;
	int			histsize;
	int			fd;
	int			i;

	if ((fd = get_histfile_fd(shell, O_CREAT | O_WRONLY | O_TRUNC)) == FAILURE)
		return ;
	entry = entry_roll_back(history->entry);
	histsize = get_histsize(shell);
	i = 0;
	while (entry != NULL)
	{
		if (history->nb_of_entries - i++ <= histsize)
			ft_putendl_fd(entry->cmd, fd);
		entry = entry->next;
	}
	close(fd);
}
