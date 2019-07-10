/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_string_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:03:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_string(t_analyzer analyzer)
{
	analyzer[P_STRING][E_STRING] = string_analyzer;
	analyzer[P_STRING][E_GREAT] = redirect_analyzer;
	analyzer[P_STRING][E_GREATAND] = redirect_analyzer;
	analyzer[P_STRING][E_LESS] = redirect_analyzer;
	analyzer[P_STRING][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_STRING][E_DGREAT] = redirect_analyzer;
	analyzer[P_STRING][E_DLESS] = redirect_analyzer;
	analyzer[P_STRING][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_STRING][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_STRING][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_STRING][E_IO_NUMBER] = io_analyzer;
	analyzer[P_STRING][E_PIPE] = flush_string;
	analyzer[P_STRING][E_DAND] = flush_string;
	analyzer[P_STRING][E_OR] = flush_string;
	analyzer[P_STRING][E_SEMICOLON] = flush_string;
	analyzer[P_STRING][E_AND] = flush_string;
	analyzer[P_STRING][E_DAND] = flush_string;
	analyzer[P_STRING][E_OR] = flush_string;
	analyzer[P_STRING][E_NEWLINE] = flush_string;
	analyzer[P_STRING][E_END] = flush_string;
}

void	init_flush_string(t_analyzer analyzer)
{
	analyzer[P_STRING_FLUSH][E_PIPE] = pipe_analyzer;
	analyzer[P_STRING_FLUSH][E_SEMICOLON] = stop_analyzer;
	analyzer[P_STRING_FLUSH][E_NEWLINE] = stop_analyzer;
	analyzer[P_STRING_FLUSH][E_AND] = stop_analyzer;
	analyzer[P_STRING_FLUSH][E_DAND] = stop_analyzer;
	analyzer[P_STRING_FLUSH][E_OR] = stop_analyzer;
	analyzer[P_STRING_FLUSH][E_END] = end_analyzer;
}

void	init_filename(t_analyzer analyzer)
{
	analyzer[P_FILENAME][E_STRING] = flush_redirect;
	analyzer[P_FILENAME][E_GREAT] = flush_redirect;
	analyzer[P_FILENAME][E_GREATAND] = flush_redirect;
	analyzer[P_FILENAME][E_LESS] = flush_redirect;
	analyzer[P_FILENAME][E_LESSAND] = flush_redirect;
	analyzer[P_FILENAME][E_DGREAT] = flush_redirect;
	analyzer[P_FILENAME][E_DLESSDASH] = flush_redirect;
	analyzer[P_FILENAME][E_DLESS] = flush_redirect;
	analyzer[P_FILENAME][E_ANDDGREAT] = flush_redirect;
	analyzer[P_FILENAME][E_IO_NUMBER] = flush_redirect;
	analyzer[P_FILENAME][E_PIPE] = flush_redirect;
	analyzer[P_FILENAME][E_SEMICOLON] = flush_redirect;
	analyzer[P_FILENAME][E_AND] = flush_redirect;
	analyzer[P_FILENAME][E_DAND] = flush_redirect;
	analyzer[P_FILENAME][E_OR] = flush_redirect;
	analyzer[P_FILENAME][E_NEWLINE] = flush_redirect;
	analyzer[P_FILENAME][E_END] = flush_redirect;
}
