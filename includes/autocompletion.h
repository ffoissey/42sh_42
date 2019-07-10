/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:22:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/04 03:43:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include "struct.h"

int8_t				autocompletion(char *input, t_registry *shell
									, char **completion, uint64_t option);
enum e_result_type	get_result_type(char *input);
char				*get_start_input(char *input, enum e_result_type type);

/*
**** Print
*/

void				print_possibilities(t_autocomplete *result);

/*
**** Tools
*/

uint8_t				is_cmd_delimiter(char c);
size_t				get_maxlen(size_t ref, size_t len);
int					lst_strcmp(void *data1, void *data2);
uint8_t				is_a_directory(char *dirname, char *file);
char				*get_home_input(char *input, t_registry *shell);
uint8_t				slash_is_missing(char *completion);
uint8_t				is_completion_dir(t_autocomplete *result,
							char **completion);

/*
**** Get Completion
*/

void				get_completion_cmd(char *input, t_autocomplete *result,
										t_registry *shell);
void				get_completion_var(char *input, t_autocomplete *result,
										t_registry *shell);
void				get_completion_file(char *input, t_autocomplete *result,
										t_registry *shell);
#endif
