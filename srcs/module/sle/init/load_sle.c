/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:05:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint64_t	assign_keycodes(t_sle *sle)
{
	sle->ak_masks[AK_ARROW_RIGHT] = AK_ARROW_RIGHT_MASK;
	sle->ak_masks[AK_ARROW_LEFT] = AK_ARROW_LEFT_MASK;
	sle->ak_masks[AK_HOME] = AK_HOME_MASK;
	sle->ak_masks[AK_END] = AK_END_MASK;
	sle->ak_masks[AK_BACKSPACE] = AK_BACKSPACE_MASK;
	sle->ak_masks[AK_DELETE] = AK_DELETE_MASK;
	sle->ak_masks[AK_CTRL_A] = AK_CTRL_A_MASK;
	sle->ak_masks[AK_CTRL_E] = AK_CTRL_E_MASK;
	sle->ak_masks[AK_CTRL_D] = AK_CTRL_D_MASK;
	sle->ak_masks[AK_CTRL_L] = AK_CTRL_L_MASK;
	sle->ak_masks[AK_ESCAPE] = AK_ESCAPE_MASK;
	sle->ak_masks[AK_ALT_V] = AK_ALT_V_MASK;
	sle->ak_masks[AK_ALT_X] = AK_ALT_X_MASK;
	sle->ak_masks[AK_ALT_C] = AK_ALT_C_MASK;
	sle->ak_masks[AK_ALT_P] = AK_ALT_P_MASK;
	sle->ak_masks[AK_CTRL_LEFT] = AK_CTRL_LEFT_MASK;
	sle->ak_masks[AK_CTRL_RIGHT] = AK_CTRL_RIGHT_MASK;
	sle->ak_masks[AK_CTRL_DOWN] = AK_CTRL_DOWN_MASK;
	sle->ak_masks[AK_CTRL_UP] = AK_CTRL_UP_MASK;
	sle->ak_masks[AK_ARROW_UP] = AK_ARROW_UP_MASK;
	sle->ak_masks[AK_ARROW_DOWN] = AK_ARROW_DOWN_MASK;
	sle->ak_masks[AK_CTRL_R] = AK_CTRL_R_MASK;
	sle->ak_masks[AK_CTRL_T] = AK_CTRL_T_MASK;
	sle->ak_masks[AK_TABULATION] = AK_TAB_MASK;
	return (SUCCESS);
}

uint64_t	set_sle_internals(t_registry *shell)
{
	if (add_var(&shell->intern, INT_PS1, INT_PS1_VALUE, SET_VAR) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_var(&shell->intern, INT_PS2, INT_PS2_VALUE, SET_VAR) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_var(&shell->intern, INT_PS3, INT_PS3_VALUE, SET_VAR) == FAILURE)
		return (INTERNAL_FAIL);
	return (SUCCESS);
}

uint64_t	init_line(t_sle *sle)
{
	if ((sle->line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	if ((sle->sub_line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	if ((sle->clip = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	if ((sle->heredocln = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	sle->search_hit = NULL;
	sle->line_save = NULL;
	return (SUCCESS);
}

uint64_t	link_keys_functions(t_actionkeys actionkeys[AK_AMOUNT])
{
	actionkeys[AK_ARROW_LEFT] = &ak_arrow_left;
	actionkeys[AK_ARROW_RIGHT] = &ak_arrow_right;
	actionkeys[AK_HOME] = &ak_home;
	actionkeys[AK_END] = &ak_end;
	actionkeys[AK_BACKSPACE] = &ak_backspace;
	actionkeys[AK_DELETE] = &ak_delete;
	actionkeys[AK_CTRL_A] = &ak_home;
	actionkeys[AK_CTRL_E] = &ak_end;
	actionkeys[AK_CTRL_D] = &ak_ctrl_d;
	actionkeys[AK_CTRL_L] = &ak_ctrl_l;
	actionkeys[AK_CTRL_UP] = &ak_ctrl_up;
	actionkeys[AK_CTRL_DOWN] = &ak_ctrl_down;
	actionkeys[AK_CTRL_LEFT] = &ak_ctrl_left;
	actionkeys[AK_CTRL_RIGHT] = &ak_ctrl_right;
	actionkeys[AK_ALT_V] = &ak_enter_visual_mode;
	actionkeys[AK_ESCAPE] = &ak_exit_modes;
	actionkeys[AK_ALT_X] = &ak_cut_selection;
	actionkeys[AK_ALT_C] = &ak_copy_selection;
	actionkeys[AK_ALT_P] = &ak_paste_clipboard;
	actionkeys[AK_ARROW_UP] = &ak_arrow_up;
	actionkeys[AK_ARROW_DOWN] = &ak_arrow_down;
	actionkeys[AK_CTRL_R] = &ak_ctrl_r;
	actionkeys[AK_CTRL_T] = &ak_ctrl_t;
	actionkeys[AK_TABULATION] = &ak_hightab;
	return (SUCCESS);
}
