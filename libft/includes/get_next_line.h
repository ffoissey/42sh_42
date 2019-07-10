/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:34:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:34:30 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_gnl_file
{
	int				fd;
	int				state;
	char			*rest;
	char			*cur;
}					t_gnl_file;

int					get_next_line(const int fd, char **line);

#endif
