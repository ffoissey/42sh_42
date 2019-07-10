/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:13:42 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	bzero_analyzer(t_analyzer analyzer)
{
	int		index;
	int		state;

	index = 0;
	while (index < ANALYZER_STATES)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			analyzer[index][state++] = error_analyzer;
		++index;
	}
}

static void	init_io_rediction_analyzer(t_analyzer analyzer)
{
	init_io(analyzer);
	init_io_redirect(analyzer);
	init_io_filename(analyzer);
	init_io_filename_and(analyzer);
	init_io_flush(analyzer);
	init_io_flush_and(analyzer);
	init_io_dup_move(analyzer);
	init_heredoc(analyzer);
	init_heredoc_redirect(analyzer);
	init_heredoc_delimiter(analyzer);
	init_io_heredoc(analyzer);
	init_io_heredoc_redirect(analyzer);
	init_dup_move(analyzer);
	init_pipe(analyzer);
	init_io_heredoc_delimiter(analyzer);
	init_flush_redirect(analyzer);
	init_assign_data(analyzer);
	init_assign_flush(analyzer);
}

t_analyzer	*init_analyzer(void)
{
	static t_analyzer analyzer;

	bzero_analyzer(analyzer);
	init_start(analyzer);
	init_stop(analyzer);
	init_error(analyzer);
	init_string(analyzer);
	init_flush_string(analyzer);
	init_redirect(analyzer);
	init_filename(analyzer);
	init_io_rediction_analyzer(analyzer);
	return (&analyzer);
}
