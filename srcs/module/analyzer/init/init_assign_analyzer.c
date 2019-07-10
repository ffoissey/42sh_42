/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assign_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:59:55 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_assign_flush(t_analyzer analyzer)
{
	analyzer[P_ASSIGN_FLUSH][E_STRING] = string_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_ASSIGN] = assign_name_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_GREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_LESS] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DGREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DLESS] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_IO_NUMBER] = io_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_SEMICOLON] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_PIPE] = pipe_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DAND] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_OR] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_AND] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_NEWLINE] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_END] = end_analyzer;
}

void	init_assign_data(t_analyzer analyzer)
{
	analyzer[P_ASSIGN_NAME][E_STRING] = assign_data_analyzer;
	analyzer[P_ASSIGN_DATA][E_STRING] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_ASSIGN] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_GREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_GREATAND] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_LESS] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_LESSAND] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DLESS] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DLESSDASH] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DGREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DLESS] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_ANDGREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_ANDDGREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_IO_NUMBER] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_PIPE] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DAND] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_OR] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_SEMICOLON] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_NEWLINE] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_END] = assign_flush_analyzer;
}

void	init_redirect(t_analyzer analyzer)
{
	analyzer[P_REDIRECT][E_STRING] = filename_analyzer;
	analyzer[P_REDIRECT_AND][E_STRING] = dup_move_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_STRING] = string_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_ASSIGN] = assign_name_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_GREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_LESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_DLESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_DGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_IO_NUMBER] = io_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_PIPE] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_AND] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_DAND] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_OR] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_SEMICOLON] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_NEWLINE] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_END] = flush_string;
}

void	init_flush_redirect(t_analyzer analyzer)
{
	analyzer[P_REDIRECT_FLUSH][E_STRING] = string_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_ASSIGN] = assign_name_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_GREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_LESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_DLESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_DGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_IO_NUMBER] = io_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_PIPE] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_SEMICOLON] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_AND] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_DAND] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_OR] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_NEWLINE] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_END] = flush_string;
}

void	init_dup_move(t_analyzer analyzer)
{
	analyzer[P_DUP_MOVE][E_STRING] = flush_redirect;
	analyzer[P_DUP_MOVE][E_ASSIGN] = flush_redirect;
	analyzer[P_DUP_MOVE][E_GREAT] = flush_redirect;
	analyzer[P_DUP_MOVE][E_GREATAND] = flush_redirect;
	analyzer[P_DUP_MOVE][E_LESS] = flush_redirect;
	analyzer[P_DUP_MOVE][E_LESSAND] = flush_redirect;
	analyzer[P_DUP_MOVE][E_DLESS] = flush_redirect;
	analyzer[P_DUP_MOVE][E_DLESSDASH] = flush_redirect;
	analyzer[P_DUP_MOVE][E_DGREAT] = flush_redirect;
	analyzer[P_DUP_MOVE][E_ANDDGREAT] = flush_redirect;
	analyzer[P_DUP_MOVE][E_IO_NUMBER] = flush_redirect;
	analyzer[P_DUP_MOVE][E_PIPE] = flush_redirect;
	analyzer[P_DUP_MOVE][E_SEMICOLON] = flush_redirect;
	analyzer[P_DUP_MOVE][E_AND] = flush_redirect;
	analyzer[P_DUP_MOVE][E_DAND] = flush_redirect;
	analyzer[P_DUP_MOVE][E_OR] = flush_redirect;
	analyzer[P_DUP_MOVE][E_NEWLINE] = flush_redirect;
	analyzer[P_DUP_MOVE][E_END] = flush_redirect;
}
