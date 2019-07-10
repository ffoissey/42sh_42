/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:36:29 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:36:31 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strendswith(char *string, char *suffix)
{
	char	*ptr;
	size_t	diff;
	size_t	suffix_len;
	size_t	string_len;

	if (!string || !suffix)
		return (-1);
	ptr = string;
	suffix_len = ft_strlen(suffix);
	string_len = ft_strlen(string);
	diff = string_len - suffix_len;
	ptr += diff;
	return (ft_strnequ(ptr, suffix, suffix_len));
}
