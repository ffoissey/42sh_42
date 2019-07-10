/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:34:38 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:34:41 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define DEFAULT_VECTOR_SIZE 64
# define DEFAULT_VECTOR_SCALE 16

typedef struct		s_vector
{
	char			*buffer;
	uint64_t		size;
	uint16_t		scale;
}					t_vector;

void				vct_del(t_vector **vector);
t_vector			*vct_new(uint64_t size);
int8_t				vct_reset(t_vector *vector);
uint64_t			vct_len(t_vector *vector);
uint64_t			vct_size(t_vector *vector);
void				vct_set_scale(t_vector *vector, uint16_t scale);
int8_t				vct_resize(t_vector *vector, uint64_t new_size);
int8_t				vct_scale(t_vector *vector);
int8_t				vct_ncpy(t_vector *dest, t_vector *src, uint64_t len);
int8_t				vct_ncat(t_vector *dest, t_vector *src, uint64_t len);
int8_t				vct_scpy(t_vector *dest, char *src, uint64_t len);
int8_t				vct_scat(t_vector *dest, char *src, uint64_t len);
char				vct_charat(t_vector *vct, uint64_t idx);
char				*vct_get_string(t_vector *vector);
char				*vct_sub(t_vector *vector, uint64_t start,
						uint64_t length);
t_vector			*vct_dups(char *str);
t_vector			*vct_dup(t_vector *vect);
int8_t				vct_insert_char(t_vector *vector, char c, uint64_t index);
int8_t				vct_del_char(t_vector *vector, uint64_t index);
int8_t				vct_insert_string(t_vector *vector, char *str,
							uint64_t index);
int8_t				vct_del_string(t_vector *vector, uint64_t start,
							uint64_t len);
int8_t				vct_replace_char(t_vector *vector, char c, uint64_t index);
int8_t				vct_replace_string(t_vector *vector, uint64_t start,
							uint64_t end, char *str);
int8_t				vct_add(t_vector *vector, char c);
int8_t				vct_push(t_vector *vector, char c);
int8_t				vct_pop(t_vector *vector);
int8_t				vct_cut(t_vector *vector);
void				shift_nleft(t_vector *vector, uint64_t start,
						uint32_t offset);
void				shift_nright(t_vector *vector, uint64_t start,
						uint32_t offset);
void				shift_left(t_vector *vector, uint64_t start);
void				shift_right(t_vector *vector, uint64_t start);
#endif
