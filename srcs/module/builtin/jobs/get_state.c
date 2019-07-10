/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:01:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	state_to_str(t_job *job, char **str)
{
	*str = ft_strnew(32);
	if (job_is_completed(job) == TRUE)
		ft_strcpy(*str, "Done");
	else if (job_is_stopped(job) == TRUE)
		ft_strcpy(*str, "Suspended");
	else
		ft_strcpy(*str, "Running");
}
