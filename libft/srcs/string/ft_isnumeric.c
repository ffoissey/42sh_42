/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 11:26:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/30 16:54:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"
#include <stdlib.h>
#include <stdint.h>

uint8_t			ft_isnumeric(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '-')
		++str;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		++str;
	}
	return (1);
}
