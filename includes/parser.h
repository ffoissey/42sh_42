/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/29 21:23:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "struct.h"

int8_t		parser(t_vector *input, t_list *lst);
uint8_t		need_subprompt(enum e_type state, enum e_type type);
uint8_t		parser_subprompt(enum e_type state, t_vector *input, t_list **lst);

/*
*************** INIT
*/

t_graph		*init_parser(void);
void		set_start_token(t_graph *tab_tokens);
void		set_word_token(t_graph *tab_tokens);
void		set_redirect_token(t_graph *tab_tokens);
void		set_assign_token(t_graph *tab_tokens);
void		set_pipe_token(t_graph *tab_tokens);
void		set_ionumber_token(t_graph *tab_tokens);

#endif
