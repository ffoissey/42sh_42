/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:35:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 20:17:31 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "struct.h"

t_list		*lexer(t_vector *line, uint8_t opt);

/*
*****************************************************
******************** INTERFACE **********************
*****************************************************
*/

void		process_maths_lexer(t_lexer *lexer);
void		out_lexer_m(t_lexer *lexer);
void		process_lexer(t_lexer *lexer);
void		out_lexer(t_lexer *lexer);

/*
*****************************************************
********************* CHECKER ***********************
*****************************************************
*/

uint8_t		is_assignation(t_lexer *lexer);
uint8_t		is_input_end(t_lexer *lexer);
uint8_t		is_delimiter(t_lexer *lexer);
uint8_t		is_io_number(t_lexer *lexer);
uint8_t		token_checker(t_lexer *lexer, int start, int end);

void		loop_quote(t_lexer *lexer);
void		loop_dbquote(t_lexer *lexer);
void		loop_braceparam(t_lexer *lexer);
void		loop_maths(t_lexer *lexer);
void		loop_par(t_lexer *lexer);

uint8_t		is_delimiter_m(t_lexer *lexer);
uint8_t		is_number_m(t_lexer *lexer);
uint8_t		is_input_end_m(t_lexer *lexer);
uint8_t		is_operator_m(t_lexer *lexer);

/*
*****************************************************
********************** TOOLS ************************
*****************************************************
*/

void		init_lexer(t_lexer *lexer, t_vector *input);
void		add_to_buffer(t_lexer *lexer);
char		get_input(t_lexer *lexer, uint8_t pos);
uint8_t		last_is_redirect(t_lexer *lexer);

/*
*****************************************************
******************* TEMP DISPLAY ********************
*****************************************************
*/

void		print_token(void *data);
void		print_mtoken(void *data);
void		lexer_print_debug(t_registry *shell, t_list *token_list);
void		lexer_m_print_debug(t_registry *shell, t_list *token_list);

#endif
