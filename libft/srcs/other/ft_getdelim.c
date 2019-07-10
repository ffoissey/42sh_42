/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdelim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:06:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 05:53:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

static t_file	*fd_manager(t_list **lst, const int fd, t_list *current)
{
	t_file			tmp;

	tmp.fd = (int)fd;
	tmp.status = 1;
	tmp.str = NULL;
	while (current)
	{
		if (((t_file *)current->data)->fd == tmp.fd)
			return (current->data);
		current = current->next;
	}
	if (!(current = ft_lstnew(&tmp, sizeof(t_file))))
		return (NULL);
	if (*lst)
		ft_lstadd(lst, current);
	return ((*lst = current)->data);
}

static int		fd_reader(t_file *current, char *buffer, char *tmp, char delim)
{
	ssize_t			n_read;

	while (!ft_strchr(current->str, delim))
	{
		ft_strclr(buffer);
		if ((n_read = read(current->fd, buffer, BUFF_SIZE)) <= 0)
			return (current->status = n_read == -1 ? -1 : 0);
		if (!(tmp = ft_strjoin(current->str, buffer)))
			return (current->status = -1);
		ft_strdel(&current->str);
		current->str = tmp;
	}
	return (current->status = 1);
}

static int		strmgmt(t_file *current, char **line, char *sub, char delim)
{
	size_t			len;
	char			tmp[2];

	tmp[0] = delim;
	tmp[1] = '\0';
	len = ft_strcspn(current->str, tmp);
	if (ft_strchr(current->str, delim))
	{
		*line = ft_strsub(current->str, 0, len);
		sub = ft_strdup(&current->str[len + 1]);
		ft_strdel(&current->str);
	}
	else
	{
		*line = current->str;
		sub = ft_strnew(1);
	}
	if (!*line || !sub)
		return (-1);
	current->str = sub;
	return (**line ? 1 : 0);
}

int				ft_getdelim(const int fd, char **line, char delim)
{
	char			buffer[BUFF_SIZE + 1];
	static t_list	*lst = NULL;
	t_file			*current;
	int				result;

	if (line == NULL || *line == 0 || fd < 0 || read(fd, buffer, 0) == -1
		|| !(current = fd_manager(&lst, fd, lst)))
		return (-1);
	ft_bzero(buffer, BUFF_SIZE + 1);
	if ((!*line && current->status == 0) || current->status == -1)
		return (current->status);
	if (fd_reader(current, buffer, NULL, delim) == -1
		|| (result = strmgmt(current, &*line, NULL, delim)) == -1)
		return (-1);
	return (result == 0 && current->status == 0 ? 0 : 1);
}
