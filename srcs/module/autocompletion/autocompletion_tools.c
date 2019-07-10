/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:01:59 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

size_t	get_maxlen(size_t ref, size_t len)
{
	return (ref >= len ? ref : len);
}

uint8_t	is_cmd_delimiter(char c)
{
	if (c == '|' || c == ';' || c == '&')
		return (TRUE);
	return (FALSE);
}

int		lst_strcmp(void *data1, void *data2)
{
	return (ft_strcmp((char *)data1, (char *)data2));
}

uint8_t	is_a_directory(char *dirname, char *file)
{
	DIR		*dir;
	char	*total_name;
	int		ok;

	total_name = NULL;
	ok = FALSE;
	ft_asprintf(&total_name, "%s/%s", dirname, file);
	if ((dir = opendir(total_name)) != NULL)
	{
		ok = TRUE;
		closedir(dir);
	}
	ft_strdel(&total_name);
	return (ok);
}

uint8_t	is_completion_dir(t_autocomplete *result, char **completion)
{
	if (result->type == FILE_TYPE && slash_is_missing(*completion) == TRUE
		&& ft_strequ(".", *completion) == FALSE)
	{
		ft_strdel(completion);
		*completion = ft_strdup("/");
		return (TRUE);
	}
	return (FALSE);
}
