/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:26:51 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	converter(long nb)
{
	if (nb > 0)
	{
		converter(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
}

void			ft_putnbr(int n)
{
	long	nb;

	nb = (long)n;
	if (n == 0)
		return (ft_putchar('0'));
	if (nb > 0)
		return (converter(nb));
	ft_putchar('-');
	return (converter(-nb));
}
