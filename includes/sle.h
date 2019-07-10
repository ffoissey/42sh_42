/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sle.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:37:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 13:37:19 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLE_H
# define SLE_H

# include "struct.h"

/*
*****************************************************
**************** PROMPT_SUBROUTINE ******************
*****************************************************
*/

uint8_t		verif_line(t_vector *line);
uint8_t		parenthesis(t_vector *line, size_t *i);
uint8_t		double_quote_routine(t_vector *line, size_t *i);
uint8_t		single_quote_routine(t_vector *line, size_t *i);
uint8_t		brace_exp_routine(t_vector *line, size_t *i);
uint8_t		maths_exp_routine(t_vector *line, size_t *i);
void		backslash_process(t_vector *line);
uint8_t		is_maths_exp(t_vector *line, int index);
uint8_t		is_brace_exp(t_vector *line, int index);
uint8_t		is_end_backslash(t_vector *line, int index);
uint8_t		subprompt_call(t_vector *line, uint32_t option);

/*
*****************************************************
************** INIT / SETTING / FREE ****************
*****************************************************
*/

uint8_t		sle(t_registry *shell, t_vector **input, uint32_t sle_flag);

uint64_t	sle_setup(t_registry *shell, t_sle *sle);
void		sle_teardown(t_sle *sle);

uint64_t	get_terminal_info(t_registry *shell);
uint64_t	init_termcaps(t_termcaps *termcp);
uint64_t	assign_keycodes(t_sle *sle);
uint64_t	link_keys_functions(t_actionkeys actionkeys[AK_AMOUNT]);
uint64_t	set_sle_internals(t_registry *shell);
uint64_t	init_line(t_sle *sle);

uint64_t	init_window(t_sle *sle);
uint64_t	init_cursor(t_sle *sle);
uint64_t	init_prompt(t_sle *sle);

t_vector	*prompt(t_registry *shell, t_sle *sle);
t_vector	*invoke_ps2prompt(t_registry *shell, t_sle *sle, uint32_t sle_flag);
t_vector	*invoke_ps3prompt(t_registry *shell, t_sle *sle);

void		handle_input_key(t_registry *shell, t_sle *sle, char c[READ_SIZE]);

void		add_redraw_flags(t_sle *sle, uint32_t flag);
void		set_redraw_flags(t_sle *sle, uint32_t rd_flag);
void		set_redraw_bounds(t_sle *sle, uint64_t s, uint64_t e);
void		set_cursor_pos(t_sle *sle, uint64_t index);
void		move_cursor(t_sle *sle);
void		move_cursor_to_coord(t_sle *sle, uint64_t x, uint64_t y);

void		update_window(t_sle *sle);
void		redraw_window(t_sle *sle);

void		redraw(t_registry *shell, t_sle *sle);
void		redrawmode_clear(t_registry *shell, t_sle *sle);
void		redrawmode_line(t_sle *sle);
void		redrawmode_last(t_sle *sle);
void		redrawmode_fptp(t_sle *sle);
void		redrawmode_fstp(t_sle *sle);
void		redrawmode_fpte(t_sle *sle);
void		redrawmode_visual(t_sle *sle);

void		define_interface_signals(void);
void		interface_resize_handler(const int signo);

void		print_char(t_sle *sle, char c);
void		print_loop(t_sle *sle, char *str);
void		print_prompt(t_registry *shell, t_sle *sle);
void		print_prompt_to_window(t_sle *sle, t_vector *text);

uint64_t	get_prompt_length(t_prompt *prompt);
void		index_to_coord(t_sle *sle, uint64_t indx, t_coord *co);

void		p_insert_name(t_vector *text, uint64_t index);
void		p_insert_username(t_sle *sle, t_vector *text, uint64_t index);
void		p_insert_cwd(t_sle *sle, t_vector *text, uint64_t index);
void		p_insert_host(t_vector *text, uint64_t index);
void		p_insert_missing(t_sle *sle, t_vector *text, uint64_t index);

/*
*****************************************************
********************  UTILS *************************
*****************************************************
*/

void		save_intern_vars(t_registry *shell, t_sle *sle);
void		find_multiline_coord(t_sle *sle, int8_t offset);
t_vector	*read_error(t_registry *shell, t_sle *sle);
uint64_t	get_prompt_length(t_prompt *prompt);
int			ft_putc(const int c);
uint8_t		is_eof(const char *buffer);
uint8_t		is_separator(char c[READ_SIZE + 1]);
uint8_t		is_printable(char c[READ_SIZE + 1]);
uint64_t	compute_mask(char c[READ_SIZE]);

uint32_t	get_next_char(const char *str, uint32_t index
						, const char direction);

void		link_actions_to_keys(int8_t (*actionkeys[AK_AMOUNT])
				(struct s_sle *sle));
void		check_nl(t_registry *shell, t_sle *sl, t_vector *line);

/*
*****************************************************
******************** ACTION KEYS ********************
*****************************************************
*/

int8_t		ak_arrow_up(t_registry *shell, t_sle *sle);
int8_t		ak_arrow_down(t_registry *shell, t_sle *sle);
int8_t		ak_arrow_left(t_registry *shell, t_sle *sle);
int8_t		ak_arrow_right(t_registry *shell, t_sle *sle);
int8_t		ak_home(t_registry *shell, t_sle *sle);
int8_t		ak_end(t_registry *shell, t_sle *sle);
int8_t		ak_delete(t_registry *shell, t_sle *sle);
int8_t		ak_backspace(t_registry *shell, t_sle *sle);

int8_t		ak_ctrl_d(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_l(t_registry *shell, t_sle *sle);

int8_t		ak_ctrl_left(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_right(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_up(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_down(t_registry *shell, t_sle *sle);

int8_t		ak_ctrl_r(t_registry *shell, t_sle *sle);
int8_t		ak_enter_visual_mode(t_registry *shell, t_sle *sle);
int8_t		ak_exit_modes(t_registry *shell, t_sle *sle);

int8_t		ak_cut_selection(t_registry *shell, t_sle *sle);
int8_t		ak_copy_selection(t_registry *shell, t_sle *sle);
int8_t		ak_paste_clipboard(t_registry *shell, t_sle *sle);

int8_t		ak_hightab(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_t(t_registry *shell, t_sle *sle);
#endif
