/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:49:32 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termcap.h>

static void				expand_prompt_extend(t_sle *sle, t_vector *text,
							int64_t index)
{
	if (vct_charat(text, index) == P_NAME)
		p_insert_name(text, index - 1);
	else if (vct_charat(text, index) == P_USER)
		p_insert_username(sle, text, index - 1);
	else if (vct_charat(text, index) == P_CWD)
		p_insert_cwd(sle, text, index - 1);
	else if (vct_charat(text, index) == P_HOST)
		p_insert_host(text, index - 1);
	else if (vct_charat(text, index) == P_MISS)
		p_insert_missing(sle, text, index - 1);
}

static void				expand_prompt(t_sle *sle, t_vector *text)
{
	int64_t	length;
	int64_t	index;

	index = -1;
	length = vct_len(text);
	while (index < length)
	{
		length = vct_len(text);
		++index;
		if (vct_get_string(text)[index] != '\\')
			continue ;
		++index;
		expand_prompt_extend(sle, text, index);
	}
}

static uint8_t			prompt_need_alignment(void)
{
	int64_t			i;
	uint64_t		pow;
	char			buff[256];
	char			ch;
	uint64_t		x;

	i = 0;
	ch = 0;
	x = 0;
	ft_bzero(buff, 256);
	write(2, "\033[6n", 4);
	while (ch != 'R' && i < 255)
	{
		read(0, &ch, 1);
		buff[i] = ch;
		i++;
	}
	i -= 2;
	pow = 1;
	while (i >= 0 && buff[i] != ';')
	{
		x = x + (buff[i--] - '0') * pow;
		pow *= 10;
	}
	return ((x != 1) ? TRUE : FALSE);
}

static void				align_prompt(t_sle *sle)
{
	tputs(sle->termcaps.standout_on, 1, &ft_putc);
	write(2, "%\n", 2);
	tputs(sle->termcaps.standout_off, 1, &ft_putc);
}

inline void				print_prompt(t_registry *shell, t_sle *sle)
{
	t_vector	*ptext;

	(void)shell;
	if (prompt_need_alignment() == TRUE)
		align_prompt(sle);
	ptext = NULL;
	if (ft_strequ(sle->prompt.state, INT_PS1))
		ptext = vct_dup(sle->interns.ps1);
	else if (ft_strequ(sle->prompt.state, INT_PS2))
		ptext = vct_dup(sle->interns.ps2);
	else if (ft_strequ(sle->prompt.state, INT_PS3))
		ptext = vct_dup(sle->interns.ps3);
	if (ptext == NULL)
		ptext = vct_dups("[ 42sh ]-> ");
	else
		expand_prompt(sle, ptext);
	print_prompt_to_window(sle, ptext);
	vct_del(&ptext);
}
