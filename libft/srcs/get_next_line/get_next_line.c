/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:35:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:35:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_protected(char const *s1, char const *s2)
{
	char	*s_new;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s_new = ft_strdup((char *)s2);
	else if (!s2)
		s_new = ft_strdup((char *)s1);
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		if (!(s_new = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
			return (NULL);
		ft_strncpy(s_new, s1, ft_strlen(s1));
		ft_strcpy(s_new + ft_strlen(s1), s2);
	}
	return (s_new);
}

static void	ft_fill_line_with_rest(t_gnl_file *file)
{
	char	*tmp;
	char	*tmp_rest;

	file->state = 0;
	if (file->rest)
	{
		if ((!(tmp = ft_strchr(file->rest, '\n'))) || (tmp && !*(tmp + 1)))
		{
			file->cur = ft_strdup(file->rest);
			if (tmp && !*(tmp + 1))
			{
				file->cur[ft_strlen(file->rest) - 1] = '\0';
				file->state = 1;
			}
			ft_strdel(&(file->rest));
		}
		else
		{
			file->cur = ft_strsub(file->rest, 0, tmp - file->rest);
			tmp_rest = file->rest;
			file->rest = ft_strdup(tmp + 1);
			ft_strdel(&tmp_rest);
			file->state = 1;
		}
	}
}

static int	ft_read(t_gnl_file *file)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	char	*tmp_cur;

	while ((ret = read(file->fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp_cur = file->cur;
		if ((tmp = ft_strchr(buf, '\n')))
		{
			file->state = 1;
			file->rest = ft_strdup(tmp + 1);
			buf[tmp - buf] = '\0';
			file->cur = ft_strjoin_protected(file->cur, buf);
			ft_strdel(&tmp_cur);
			return (SUCCESS);
		}
		file->cur = ft_strjoin_protected(file->cur, buf);
		ft_strdel(&tmp_cur);
	}
	if (file->cur && file->cur[0] != '\0')
		file->state = 1;
	return (ret == -1 ? -1 : file->state);
}

int			get_next_line(const int fd, char **line)
{
	static	t_gnl_file	file;

	if (fd < 0 || !line)
		return (FAILURE);
	file.fd = fd;
	ft_fill_line_with_rest(&file);
	if (file.state != 1 && ft_read(&file) == FAILURE)
		return (FAILURE);
	if (file.cur != NULL)
	{
		*line = ft_strdup(file.cur);
		ft_strdel(&file.cur);
	}
	return ((*line == NULL && file.state != 0) ? FAILURE : file.state);
}
