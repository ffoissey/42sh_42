/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termmode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:54:42 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termios.h>
#include <unistd.h>

static int16_t			init_term_modes(void)
{
	struct termios term;

	if ((g_shell->orig_ios = malloc(sizeof(struct termios))) == NULL)
		return (CRITICAL_ERROR | MALLOC_FAIL);
	if ((g_shell->sle_ios = malloc(sizeof(struct termios))) == NULL)
		return (CRITICAL_ERROR | MALLOC_FAIL);
	if ((g_shell->exe_ios = malloc(sizeof(struct termios))) == NULL)
		return (CRITICAL_ERROR | MALLOC_FAIL);
	if (tcgetattr(STDIN_FILENO, &term) != SUCCESS)
		return (CRITICAL_ERROR | TERMMDE_FAIL);
	ft_memcpy(g_shell->orig_ios, &term, sizeof(struct termios));
	term.c_lflag &= ~TOSTOP;
	ft_memcpy(g_shell->exe_ios, &term, sizeof(struct termios));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag |= ISIG;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	ft_memcpy(g_shell->sle_ios, &term, sizeof(struct termios));
	return (SUCCESS);
}

static int16_t			set_mode(struct termios *mode)
{
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, mode) != SUCCESS)
		return (FAILURE | TERMMDE_FAIL);
	return (SUCCESS);
}

int16_t					term_mode(uint8_t mode_flag)
{
	if (mode_flag == TERMMODE_INIT)
		return (init_term_modes());
	else if (mode_flag == TERMMODE_DFLT)
		return (set_mode(g_shell->orig_ios));
	else if (mode_flag == TERMMODE_SLE)
		return (set_mode(g_shell->sle_ios));
	else if (mode_flag == TERMMODE_EXEC)
		return (set_mode(g_shell->exe_ios));
	return (SUCCESS);
}
