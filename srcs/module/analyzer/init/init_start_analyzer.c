/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:05:16 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_start(t_analyzer analyzer)
{
	analyzer[P_START][E_STRING] = string_analyzer;
	analyzer[P_START][E_ASSIGN] = assign_name_analyzer;
	analyzer[P_START][E_GREAT] = redirect_analyzer;
	analyzer[P_START][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_START][E_LESS] = redirect_analyzer;
	analyzer[P_START][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_START][E_DGREAT] = redirect_analyzer;
	analyzer[P_START][E_DLESS] = redirect_analyzer;
	analyzer[P_START][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_START][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_START][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_START][E_IO_NUMBER] = io_analyzer;
	analyzer[P_START][E_NEWLINE] = stop_analyzer;
	analyzer[P_START][E_END] = end_analyzer;
}

void	init_stop(t_analyzer analyzer)
{
	analyzer[P_STOP][E_STRING] = string_analyzer;
	analyzer[P_STOP][E_ASSIGN] = assign_name_analyzer;
	analyzer[P_STOP][E_GREAT] = redirect_analyzer;
	analyzer[P_STOP][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_STOP][E_LESS] = redirect_analyzer;
	analyzer[P_STOP][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_STOP][E_DGREAT] = redirect_analyzer;
	analyzer[P_STOP][E_DLESS] = redirect_analyzer;
	analyzer[P_STOP][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_STOP][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_STOP][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_STOP][E_IO_NUMBER] = io_analyzer;
	analyzer[P_STOP][E_PIPE] = pipe_analyzer;
	analyzer[P_STOP][E_SEMICOLON] = stop_analyzer;
	analyzer[P_STOP][E_AND] = stop_analyzer;
	analyzer[P_STOP][E_NEWLINE] = stop_analyzer;
	analyzer[P_STOP][E_END] = end_analyzer;
}

void	init_error(t_analyzer analyzer)
{
	analyzer[P_ERROR][E_STRING] = end_analyzer;
	analyzer[P_ERROR][E_ASSIGN] = end_analyzer;
	analyzer[P_ERROR][E_GREAT] = end_analyzer;
	analyzer[P_ERROR][E_GREATAND] = end_analyzer;
	analyzer[P_ERROR][E_LESS] = end_analyzer;
	analyzer[P_ERROR][E_LESSAND] = end_analyzer;
	analyzer[P_ERROR][E_DGREAT] = end_analyzer;
	analyzer[P_ERROR][E_DLESS] = end_analyzer;
	analyzer[P_ERROR][E_DLESSDASH] = end_analyzer;
	analyzer[P_ERROR][E_ANDGREAT] = end_analyzer;
	analyzer[P_ERROR][E_ANDDGREAT] = end_analyzer;
	analyzer[P_ERROR][E_IO_NUMBER] = end_analyzer;
	analyzer[P_ERROR][E_SEMICOLON] = stop_analyzer;
	analyzer[P_ERROR][E_PIPE] = pipe_analyzer;
	analyzer[P_ERROR][E_AND] = stop_analyzer;
	analyzer[P_ERROR][E_NEWLINE] = stop_analyzer;
	analyzer[P_ERROR][E_END] = end_analyzer;
}
