/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:54:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_io(t_analyzer analyzer)
{
	analyzer[P_IO][E_GREAT] = io_redirect_analyzer;
	analyzer[P_IO][E_DGREAT] = io_redirect_analyzer;
	analyzer[P_IO][E_LESS] = io_redirect_analyzer;
	analyzer[P_IO][E_DLESS] = io_redirect_analyzer;
	analyzer[P_IO][E_DLESSDASH] = io_redirect_analyzer;
	analyzer[P_IO][E_GREATAND] = io_redirect_and_analyzer;
	analyzer[P_IO][E_LESSAND] = io_redirect_and_analyzer;
}

void	init_io_filename(t_analyzer analyzer)
{
	analyzer[P_IO_FILENAME][E_STRING] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_GREAT] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_GREATAND] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_LESS] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_LESSAND] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_DGREAT] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_DLESS] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_DLESSDASH] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_ANDDGREAT] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_PIPE] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_IO_NUMBER] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_SEMICOLON] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_PIPE] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_AND] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_DAND] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_OR] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_NEWLINE] = io_redirect_flush;
	analyzer[P_IO_FILENAME][E_END] = io_redirect_flush;
}

void	init_io_filename_and(t_analyzer analyzer)
{
	analyzer[P_IO_REDIRECT_AND][E_STRING] = io_dup_move_analyzer;
}

void	init_io_flush(t_analyzer analyzer)
{
	analyzer[P_IO_FLUSH][E_STRING] = string_analyzer;
	analyzer[P_IO_FLUSH][E_GREAT] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_GREATAND] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_LESS] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_LESSAND] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_DGREAT] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_DLESS] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_IO_FLUSH][E_IO_NUMBER] = io_analyzer;
	analyzer[P_IO_FLUSH][E_PIPE] = flush_string;
	analyzer[P_IO_FLUSH][E_SEMICOLON] = flush_string;
	analyzer[P_IO_FLUSH][E_AND] = flush_string;
	analyzer[P_IO_FLUSH][E_DAND] = flush_string;
	analyzer[P_IO_FLUSH][E_OR] = flush_string;
	analyzer[P_IO_FLUSH][E_NEWLINE] = flush_string;
	analyzer[P_IO_FLUSH][E_END] = flush_string;
}

void	init_io_flush_and(t_analyzer analyzer)
{
	analyzer[P_IO_FLUSH_AND][E_STRING] = string_analyzer;
	analyzer[P_IO_FLUSH_AND][E_GREAT] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_GREATAND] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_LESS] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_LESSAND] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_DGREAT] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_DLESS] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_IO_FLUSH_AND][E_IO_NUMBER] = io_analyzer;
	analyzer[P_IO_FLUSH_AND][E_PIPE] = flush_string;
	analyzer[P_IO_FLUSH_AND][E_SEMICOLON] = flush_string;
	analyzer[P_IO_FLUSH_AND][E_DAND] = flush_string;
	analyzer[P_IO_FLUSH_AND][E_OR] = flush_string;
	analyzer[P_IO_FLUSH_AND][E_AND] = flush_string;
	analyzer[P_IO_FLUSH_AND][E_NEWLINE] = flush_string;
	analyzer[P_IO_FLUSH_AND][E_END] = flush_string;
}
