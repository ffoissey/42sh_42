/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:30:52 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint32_t		write_esc_sequence(char *str, uint32_t index)
{
	char		*esc;
	uint32_t	length;

	esc = NULL;
	length = 2;
	if (str[index + length] != '[')
		return (length - 1);
	while (str[++length + index] != '\0')
	{
		if (str[length + index] != ';'
				&& str[length + index] != 'm'
				&& !ft_isdigit(str[length + index]))
			return (length);
		if (str[index + length] == 'm')
		{
			esc = ft_strsub(str, index + 1, length);
			esc[0] = 27;
			ft_dprintf(2, "%s", esc);
			ft_strdel(&esc);
			break ;
		}
	}
	return (length + 1);
}

void			print_prompt_to_window(t_sle *sle, t_vector *text)
{
	uint32_t	index;
	char		*str;

	index = 0;
	str = vct_get_string(text);
	while (str[index] != '\0')
	{
		if (str[index] == '\\' && str[index + 1] == 'e')
			index += write_esc_sequence(str, index);
		write(2, &str[index], 1);
		++index;
		if (sle->cursor.x == sle->window.cols)
		{
			sle->cursor.y++;
			sle->cursor.x = 0;
		}
		sle->cursor.x++;
	}
	sle->prompt.length = (sle->cursor.y * sle->window.cols) + sle->cursor.x;
}
