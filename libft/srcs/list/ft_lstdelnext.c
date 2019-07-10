/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:08:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/06 20:51:42 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelnext(t_list *current, void f(void *))
{
	t_list *next;

	next = current->next->next;
	ft_lstdelone(&current->next, f);
	current->next = next;
}
