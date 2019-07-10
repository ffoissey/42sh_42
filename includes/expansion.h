/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nrechati <Nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 02:50:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 16:42:16 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"

char			*expansion_pipeline(t_list *intern_var, char *str);
char			*expansion_word(t_list *intern_var, char *str);
char			*arithmetic_expansion(char *input);
char			*expand_string(t_list *lst, char *str);
char			*tilde(t_list *intern_var, char *str);
char			*variable_expansion(t_list *intern_var, char *str);
void			quote_removal(char *str);
char			character_swap(char swapped);
void			delete_character(char *str);
t_quote			select_quoting(t_quote quote, char c);
int				check_backslash(char *dest, t_quote quote, int i);

int				parameter_expansion(t_list *intern, char **dest
										, int i);
int				parameter_get(t_list *intern
										, t_parameter *parameter);
int				parameter_parse(t_list *intern
										, t_parameter *parameter);
void			parameter_lexer(t_parameter *parameter);
void			generate_pex_token(t_parameter *param);
void			pex_word(t_parameter *param);
int				replace_expansion(t_list *intern, t_parameter *param
				, int mode);
int				exists_expansion(t_list *intern, t_parameter *param
				, int mode);
int				assign_expansion(t_list *intern, t_parameter *param
				, int mode);
int				default_expansion(t_list *intern, t_parameter *param
				, int mode);
int				prefix_expansion(t_list *intern, t_parameter *param
				, int mode);
int				suffix_expansion(t_list *intern, t_parameter *param
				, int mode);

int				get_delimiter(t_parameter *param
								, t_pex_token *token);

void			parameter_print_debug(t_list *token_list);

int8_t			calcul(t_stack *rpn, t_stack *solve);
int8_t			arithmetic_analyzer(t_arithmetic *arithmetic);
int8_t			find_expansion_end(t_arithmetic *arithmetic
						, char *input, size_t start);
int8_t			get_expansion_input(t_arithmetic *arithmetic
						, char *input, size_t start);

void			m_number_analyzer(t_arithmetic *arithmetic);
void			m_unary_analyzer(t_arithmetic *arithmetic);
void			m_operator_analyzer(t_arithmetic *arithmetic);
void			m_logical_operator(t_arithmetic *arithmetic);
void			m_preffix(t_arithmetic *arithmetic);
void			m_suffix(t_arithmetic *arithmetic);
void			m_parenthesis_analyzer(t_arithmetic *arithmetic);
void			m_variable_analyzer(t_arithmetic *arithmetic);
void			m_flush_variable_analyzer(t_arithmetic *arithmetic);
void			m_error_analyzer(t_arithmetic *arithmetic);
void			m_end_analyzer(t_arithmetic *arithmetic);

void			convert_plus_minus(t_token *token
										, t_rpn_tk *current);
void			m_get_token(t_arithmetic *arithmetic
										, t_list **node);

void			del_infix(t_infix *infix);
int				del_arithmetic(t_arithmetic *arithmetic, char **output);

int8_t			calculator(t_infix *infix);
uint8_t			need_pop_operator(t_rpn_tk *curr
										, t_stack *operator);
uint8_t			is_left_p(t_stack *operator);
int8_t			ft_shunting_yds(t_stack *infix, t_stack *rpn);
int8_t			calculate_rpn(t_stack *rpn, t_infix *infix);
void			do_logical(t_rpn_tk *first, t_rpn_tk *second
										, t_rpn_tk *curr);
void			do_compare(t_rpn_tk *first, t_rpn_tk *second
										, t_rpn_tk *curr);
void			do_high_op(t_rpn_tk *first, t_rpn_tk *second
										, t_rpn_tk *curr);
void			do_low_op(t_rpn_tk *first, t_rpn_tk *second
										, t_rpn_tk *curr);
void			do_unary(t_rpn_tk *number, t_rpn_tk *curr);

t_ar_analyzer	*init_math_analyzer(void);
void			init_m_flush_variable(t_ar_analyzer analyzer);
void			init_m_variable(t_ar_analyzer analyzer);
void			init_m_number(t_ar_analyzer analyzer);
void			init_m_operator(t_ar_analyzer analyzer);
void			init_m_unary(t_ar_analyzer analyzer);
void			init_m_close_parent(t_ar_analyzer analyzer);
void			init_m_open_parent(t_ar_analyzer analyzer);
void			init_m_start(t_ar_analyzer analyzer);

#endif
