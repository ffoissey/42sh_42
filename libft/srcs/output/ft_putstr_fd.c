/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:29:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int		ft_putstr_fd(char const *str, int fd)
{
	if (!str)
		return (0);
	return (write(fd, str, ft_strlen(str)));
}
