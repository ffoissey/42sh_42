/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_analyzer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:07:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_heredoc_delimiter(t_analyzer analyzer)
{
	analyzer[P_HEREDOC_DELIMITER][E_STRING] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_IO_NUMBER] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_GREAT] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_GREATAND] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_LESS] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_DLESS] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_DLESSDASH] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_LESSAND] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_DGREAT] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_ANDDGREAT] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_PIPE] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_SEMICOLON] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_AND] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_DAND] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_OR] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_NEWLINE] = heredoc_analyzer;
	analyzer[P_HEREDOC_DELIMITER][E_END] = heredoc_analyzer;
}

void	init_heredoc_redirect(t_analyzer analyzer)
{
	analyzer[P_IO_HEREDOC_REDIRECT][E_STRING] = heredoc_delimiter;
	analyzer[P_HEREDOC_REDIRECT][E_STRING] = heredoc_delimiter;
}

void	init_io_heredoc(t_analyzer analyzer)
{
	analyzer[P_IO_HEREDOC][E_STRING] = string_analyzer;
	analyzer[P_IO_HEREDOC][E_IO_NUMBER] = io_analyzer;
	analyzer[P_IO_HEREDOC][E_GREAT] = redirect_analyzer;
	analyzer[P_IO_HEREDOC][E_GREATAND] = redirect_analyzer;
	analyzer[P_IO_HEREDOC][E_LESS] = redirect_analyzer;
	analyzer[P_IO_HEREDOC][E_LESSAND] = redirect_analyzer;
	analyzer[P_IO_HEREDOC][E_DGREAT] = redirect_analyzer;
	analyzer[P_IO_HEREDOC][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_IO_HEREDOC][E_PIPE] = flush_string;
	analyzer[P_IO_HEREDOC][E_SEMICOLON] = flush_string;
	analyzer[P_IO_HEREDOC][E_AND] = flush_string;
	analyzer[P_IO_HEREDOC][E_DAND] = flush_string;
	analyzer[P_IO_HEREDOC][E_OR] = flush_string;
	analyzer[P_IO_HEREDOC][E_NEWLINE] = flush_string;
	analyzer[P_IO_HEREDOC][E_END] = flush_string;
}

void	init_io_heredoc_delimiter(t_analyzer analyzer)
{
	analyzer[P_IO_HEREDOC_DELIMITER][E_STRING] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_IO_NUMBER] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_GREAT] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_GREATAND] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_LESS] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_LESSAND] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_DGREAT] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_ANDDGREAT] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_PIPE] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_SEMICOLON] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_AND] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_DAND] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_OR] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_NEWLINE] = io_heredoc_analyzer;
	analyzer[P_IO_HEREDOC_DELIMITER][E_END] = io_heredoc_analyzer;
}

void	init_heredoc(t_analyzer analyzer)
{
	analyzer[P_HEREDOC][E_STRING] = string_analyzer;
	analyzer[P_HEREDOC][E_IO_NUMBER] = io_analyzer;
	analyzer[P_HEREDOC][E_GREAT] = redirect_analyzer;
	analyzer[P_HEREDOC][E_GREATAND] = redirect_analyzer;
	analyzer[P_HEREDOC][E_LESS] = redirect_analyzer;
	analyzer[P_HEREDOC][E_DLESS] = redirect_analyzer;
	analyzer[P_HEREDOC][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_HEREDOC][E_LESSAND] = redirect_analyzer;
	analyzer[P_HEREDOC][E_DGREAT] = redirect_analyzer;
	analyzer[P_HEREDOC][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_HEREDOC][E_PIPE] = flush_string;
	analyzer[P_HEREDOC][E_SEMICOLON] = flush_string;
	analyzer[P_HEREDOC][E_AND] = flush_string;
	analyzer[P_HEREDOC][E_DAND] = flush_string;
	analyzer[P_HEREDOC][E_OR] = flush_string;
	analyzer[P_HEREDOC][E_NEWLINE] = flush_string;
	analyzer[P_HEREDOC][E_END] = flush_string;
}
