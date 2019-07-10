/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:54:20 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/04 13:49:59 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# define GET_HEAD		0x01
# define FLUSH_MEMORY	0x02
# define PRINT			0x04
# define SILENCE		0x08

/*
**	ifdef GC
**	define ft_malloc(x)	ft_malloc_up(x, __func__, __FILE__, __LINE__)
**	else
**	define ft_free free
**	define ft_malloc malloc
**	endif
*/

typedef struct	s_meminfo
{
	void		*addr;
	size_t		size;
	size_t		stack_size;
	char		**stack_fct;
	const char	*function;
	const char	*file;
	char		time[23];
	int			line;
}				t_meminfo;

/*
**void	del_meminfo(t_list **lst);
**void	*ft_malloc_up(size_t size, const char *function_name, const char *file,
**					const int line);
**void	ft_free(void *ptr);
**void	ft_flush_memory(uint8_t opt);
**void	*ft_get_head_list_allocation(uint8_t opt);
*/
#endif
