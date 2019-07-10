/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:34:58 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:34:59 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static void			s_conv(long long nb, char *base, int index, char *buffer)
{
	if (nb == 0 && index == 0)
	{
		buffer[0] = base[0];
		buffer[1] = '\0';
		return ;
	}
	if (nb > 0)
	{
		s_conv(nb / ft_strlen(base), base, index + 1, buffer);
		buffer[index] = base[nb % ft_strlen(base)];
		return ;
	}
	buffer[index] = '\0';
	return ;
}

static void			u_conv(unsigned long long nb, char *base, int id, char *buf)
{
	if (nb == 0 && id == 0)
	{
		buf[0] = base[0];
		buf[1] = '\0';
		return ;
	}
	if (nb > 0)
	{
		u_conv(nb / ft_strlen(base), base, id + 1, buf);
		buf[id] = base[nb % ft_strlen(base)];
		return ;
	}
	buf[id] = '\0';
	return ;
}

char				*convert_sign(char *nbr, char *base_from, char *base_to)
{
	char		buffer[BASE_MAX];
	char		*conv_res;
	long long	base_ten;
	int			buff_len;
	int			i;

	i = ft_isdigit(*nbr) ? 0 : 1;
	if (i)
		buffer[0] = *nbr;
	base_ten = ft_atoll_base(nbr, base_from);
	s_conv(base_ten, base_to, i, buffer);
	buff_len = ft_strlen(buffer);
	if (!(conv_res = ft_strnew(buff_len + i)))
		return (NULL);
	conv_res[0] = buffer[0] == '-' ? '-' : '0';
	while (buff_len >= 0)
		conv_res[i++] = buffer[--buff_len];
	i = buffer[0] == '-' ? i - 1 : i - 0;
	conv_res[i] = '\0';
	return (conv_res);
}

char				*convert_unsign(char *nbr, char *base_from, char *base_to)
{
	char				buffer[BASE_MAX];
	char				*conv_res;
	unsigned long long	base_ten;
	int					buff_len;
	int					i;

	i = 0;
	base_ten = ft_atoull_base(nbr, base_from);
	u_conv(base_ten, base_to, i, buffer);
	buff_len = ft_strlen(buffer);
	if (!(conv_res = ft_strnew(buff_len)))
		return (NULL);
	while (buff_len >= 0)
		conv_res[i++] = buffer[--buff_len];
	conv_res[i - 1] = '\0';
	return (conv_res);
}

char				*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	if (*nbr == '-' || *nbr == '+')
		return (convert_sign(nbr, base_from, base_to));
	else
		return (convert_unsign(nbr, base_from, base_to));
}
