/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void				prompt_pre_process(t_sle *sle)
{
	mark_proc_status();
	notify_job_info(g_shell->job_list, "Done");
	sle->state = STATE_STD;
	vct_reset(sle->line);
	vct_reset(sle->sub_line);
	vct_reset(sle->window.displayed_line);
	history(NULL, NULL, RESET_HEAD);
	update_window(sle);
}

static int8_t			prompt_post_process(t_registry *shell, t_sle *sle)
{
	if ((sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
			&& sle->search_hit != NULL)
	{
		vct_reset(sle->line);
		vct_ncpy(sle->line, sle->search_hit, vct_len(sle->search_hit));
		vct_del(&sle->search_hit);
		sle->search_hit = NULL;
	}
	sle->state = STATE_STD;
	autocompletion(NULL, shell, NULL, RESET_RESULT);
	history(NULL, NULL, RESET_HEAD);
	vct_add(sle->line, '\n');
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	redraw(shell, sle);
	ft_putendl_fd("", 2);
	if (ft_strequ(sle->prompt.state, INT_PS1) == TRUE)
	{
		if (verif_line(sle->line) == FALSE)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_vector				*prompt(t_registry *shell, t_sle *sle)
{
	char		character[READ_SIZE + 1];

	prompt_pre_process(sle);
	ft_bzero(character, READ_SIZE + 1);
	print_prompt(shell, sle);
	while (is_separator(character) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (is_eof(vct_get_string(sle->line)) == TRUE)
		{
			ft_putchar_fd('\n', 2);
			return (NULL);
		}
		if (read(STDIN_FILENO, character, READ_SIZE) == FAILURE)
			return (read_error(shell, sle));
		handle_input_key(shell, sle, character);
		redraw(shell, sle);
	}
	if (prompt_post_process(shell, sle) == FAILURE)
		vct_reset(sle->line);
	return (vct_dup(sle->line));
}

t_vector				*invoke_ps2prompt(t_registry *shell, t_sle *sle,
							uint32_t sle_flag)
{
	t_vector			*linesave;
	t_vector			*line;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR,
										PROMPT_BRACE, PROMPT_MATHS};

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.missing_char = (char *)prompt_type[sle_flag & ~SLE_PS2_PROMPT];
	sle->prompt.state = INT_PS2;
	if ((line = prompt(shell, sle)) == NULL)
	{
		sle->line = linesave;
		return (NULL);
	}
	vct_del(&line);
	sle->line = linesave;
	return (vct_dup(sle->sub_line));
}

t_vector				*invoke_ps3prompt(t_registry *shell, t_sle *sle)
{
	t_vector	*linesave;
	t_vector	*line;

	linesave = sle->line;
	sle->line = sle->heredocln;
	sle->prompt.state = INT_PS3;
	if ((line = prompt(shell, sle)) == NULL)
	{
		sle->line = linesave;
		return (NULL);
	}
	vct_del(&line);
	sle->line = linesave;
	check_nl(shell, sle, sle->heredocln);
	return (vct_dup(sle->heredocln));
}
