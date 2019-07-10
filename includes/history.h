/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:33:24 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 20:17:07 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H
# include "struct.h"

/*
*****************
**** HISTORY ****
*****************
*/

char		*history(t_registry *shell, const char *name,
					const uint64_t option);
char		*get_entry(t_history *history, const char *search,
					const uint64_t option);
void		print_history(t_history *history, const char *elem,
					uint64_t option);
void		read_histfile(t_registry *shell, t_history *history);
void		write_histfile(t_registry *shell, t_history *history);
t_entry		*entry_roll_back(t_entry *entry);

/*
*****************
***** ENTRY *****
*****************
*/

void		add_entry(t_entry **head, t_entry *new_entry);
t_entry		*create_entry(const char *cmd);
void		free_history(t_entry *entry);
void		pop_entry(t_entry **entry, t_entry **head);

/*
*****************
*** EXPANSION ***
*****************
*/

int8_t		history_expansion(t_vector *input);

/*
*****************
***** TOOLS *****
*****************
*/

t_entry		*entry_roll_back(t_entry *entry);
void		int_swap(int *nb1, int *nb2);

#endif
