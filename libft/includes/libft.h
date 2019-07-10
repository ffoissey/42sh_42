/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:55:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/04 19:37:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BASE_MAX 66
# define SUCCESS 0
# define FAILURE -1
# define TRUE 1
# define FALSE 0

# include <string.h>
# include "ft_printf.h"
# include "list.h"
# include "directory.h"
# include "str.h"
# include "memory.h"
# include "output.h"
# include "conversion.h"
# include "test.h"
# include "other.h"
# include "hashmap.h"
# include "vector.h"
# include "get_next_line.h"

void				ft_freetab(char ***t);
char				**ft_getargstab(int ac, char **av);
void				ft_showtab(char **t);
int					ft_tabsize(char **tab);
int					ft_taboneach(char **current, void *context
								, char *(*mod)(char *, void *));
int					ft_getopt(int ac, char **av, const char *optstr);
#endif
