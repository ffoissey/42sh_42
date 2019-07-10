/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/28 20:13:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
# include "struct.h"

void	log_print(t_registry *reg, const char *importance,
						const char *message, ...);
void	init_debug_logger(t_registry *reg);
void	analyzer_print_debug(t_registry *shell, t_list *command_group);
void	print_command(void *data);

#endif
