/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io_redirect_analyzer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:56:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_io_redirect(t_analyzer analyzer)
{
	analyzer[P_IO_REDIRECT][E_STRING] = filename_analyzer;
}

void	init_pipe(t_analyzer analyzer)
{
	analyzer[P_PIPE][E_STRING] = string_analyzer;
	analyzer[P_PIPE][E_GREAT] = redirect_analyzer;
	analyzer[P_PIPE][E_GREATAND] = redirect_analyzer;
	analyzer[P_PIPE][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_PIPE][E_LESS] = redirect_analyzer;
	analyzer[P_PIPE][E_DLESS] = redirect_analyzer;
	analyzer[P_PIPE][E_LESSAND] = redirect_analyzer;
	analyzer[P_PIPE][E_DGREAT] = redirect_analyzer;
	analyzer[P_PIPE][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_PIPE][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_PIPE][E_IO_NUMBER] = io_analyzer;
}

void	init_io_dup_move(t_analyzer analyzer)
{
	analyzer[P_IO_DUP_MOVE][E_STRING] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_GREAT] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_GREATAND] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_LESS] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_LESSAND] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_DGREAT] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_DLESS] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_DLESSDASH] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_ANDDGREAT] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_IO_NUMBER] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_PIPE] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_SEMICOLON] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_DAND] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_OR] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_AND] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_NEWLINE] = io_and_redirect_flush;
	analyzer[P_IO_DUP_MOVE][E_END] = io_and_redirect_flush;
}

void	init_io_heredoc_redirect(t_analyzer analyzer)
{
	analyzer[P_IO_HEREDOC_REDIRECT][E_STRING] = heredoc_delimiter;
}
