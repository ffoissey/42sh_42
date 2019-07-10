/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_graph		*init_parser(void)
{
	static t_graph	graph[NB_OF_TOKENS];

	ft_bzero(&graph, sizeof(graph));
	set_start_token(graph);
	set_word_token(graph);
	set_redirect_token(graph);
	set_assign_token(graph);
	set_pipe_token(graph);
	set_ionumber_token(graph);
	return (graph);
}
