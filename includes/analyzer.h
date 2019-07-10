/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 06:07:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_H
# define ANALYZER_H
# include "struct.h"

t_list		*analyzer(t_list **tokens);
void		reset_analyzer(t_registry *shell, t_analyze *analyze);
t_analyzer	*init_analyzer(void);
void		delete_analyzer(t_analyze *analyze);
void		start_analyzer(t_analyze *analyze);
void		stop_analyzer(t_analyze *analyze);
void		end_analyzer(t_analyze *analyze);
void		error_analyzer(t_analyze *analyze);

void		string_analyzer(t_analyze *analyze);
void		special_string_analyzer(t_analyze *analyze);
void		flush_string(t_analyze *analyze);

void		assign_name_analyzer(t_analyze *analyze);
void		assign_data_analyzer(t_analyze *analyze);
void		assign_flush_analyzer(t_analyze *analyze);

void		redirect_analyzer(t_analyze *analyze);
void		redirect_and_analyzer(t_analyze *analyze);
void		pipe_analyzer(t_analyze *analyze);
void		filename_analyzer(t_analyze *analyze);
void		dup_move_analyzer(t_analyze *analyze);
void		flush_redirect(t_analyze *analyze);
void		flush_redirect_and(t_analyze *analyze);

void		default_io(char *tty_name);
void		io_analyzer(t_analyze *analyze);
void		io_redirect_analyzer(t_analyze *analyze);
void		io_redirect_and_analyzer(t_analyze *analyze);
void		io_dup_move_analyzer(t_analyze *analyze);
void		io_filename_analyzer(t_analyze *analyze);
void		io_and_redirect_flush(t_analyze *analyze);
void		io_redirect_flush(t_analyze *analyze);
int			define_io_dup_move(t_token *token);

void		heredoc_analyzer(t_analyze *analyze);
void		io_heredoc_analyzer(t_analyze *analyze);
void		heredoc_delimiter(t_analyze *analyze);

int			is_ionumber(t_analyze *analyze, char *str);
void		check_filename(t_analyze *analyze);
void		set_group_type(t_group *group, t_action *action);
t_type		pop_token_type(t_stack *stack);
char		*pop_token_data(t_stack *stack);
void		get_token(t_analyze *analyze);
void		generate_filedesc(t_analyze *analyze, int first, int second
					, int action);

/*
*************** INIT
*/

void		init_start(t_analyzer analyzer);
void		init_stop(t_analyzer analyzer);
void		init_error(t_analyzer analyzer);
void		init_assign_name(t_analyzer analyzer);
void		init_assign_data(t_analyzer analyzer);
void		init_assign_flush(t_analyzer analyzer);
void		init_io(t_analyzer analyzer);
void		init_io_filename(t_analyzer analyzer);
void		init_io_filename_and(t_analyzer analyzer);
void		init_io_flush(t_analyzer analyzer);
void		init_io_flush_and(t_analyzer analyzer);
void		init_io_redirect(t_analyzer analyzer);
void		init_pipe(t_analyzer analyzer);
void		init_io_dup_move(t_analyzer analyzer);
void		init_io_redirect(t_analyzer analyzer);
void		init_io_move(t_analyzer analyzer);
void		init_io_dup(t_analyzer analyzer);
void		init_io_heredoc_redirect(t_analyzer analyzer);
void		init_io_heredoc_delimiter(t_analyzer analyzer);
void		init_io_heredoc(t_analyzer analyzer);
void		init_string(t_analyzer analyzer);
void		init_special_string(t_analyzer analyzer);
void		init_flush_string(t_analyzer analyzer);
void		init_filename(t_analyzer analyzer);
void		init_separator(t_analyzer analyzer);
void		init_redirect(t_analyzer analyzer);
void		init_dup_move(t_analyzer analyzer);
void		init_flush_redirect(t_analyzer analyzer);
void		init_pipe(t_analyzer analyzer);
void		init_heredoc(t_analyzer analyzer);
void		init_heredoc_redirect(t_analyzer analyzer);
void		init_heredoc_delimiter(t_analyzer analyzer);

#endif
