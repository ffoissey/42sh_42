/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:15:16 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*extract_path(char *input)
{
	char	*path;
	size_t	len;

	if (input == NULL)
		return (NULL);
	path = ft_strdup(input);
	len = ft_strlen(input) - 1;
	while (len > 0 && path[len])
	{
		if (path[len - 1] == '/')
		{
			path[len] = '\0';
			break ;
		}
		len--;
	}
	return (path);
}

static void		add_file_to_list(t_autocomplete *result,
						char *dirname, char *d_name)
{
	char				*data;

	data = NULL;
	if (is_a_directory(dirname, d_name) == TRUE)
		ft_asprintf(&data, "%s/", d_name);
	else
		ft_asprintf(&data, "%s ", d_name);
	ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
	result->max_len = get_maxlen(result->max_len, ft_strlen(data));
	ft_strdel(&data);
	result->nb++;
}

static void		get_file_list(char *dirname, char *input,
						t_autocomplete *result, DIR *dir)
{
	struct dirent		*mydir;
	char				*fusion;
	size_t				len;

	result->nb = 0;
	len = input == NULL ? 0 : ft_strlen(input);
	while ((mydir = readdir(dir)) != NULL)
	{
		if ((ft_strequ(mydir->d_name, ".")
			|| ft_strequ(mydir->d_name, ".."))
			&& len > 0 && input[len - 1] != '.')
			continue ;
		fusion = NULL;
		if (dirname[ft_strlen(dirname) - 1] == '/' || mydir->d_name[0] == '/')
			ft_asprintf(&fusion, "%s%s", dirname, mydir->d_name);
		else
			ft_asprintf(&fusion, "%s/%s", dirname, mydir->d_name);
		if (len == 0 || ft_strnequ(fusion, input, len) == TRUE)
			add_file_to_list(result, dirname, mydir->d_name);
		ft_strdel(&fusion);
	}
}

static void		get_path_and_transform(t_autocomplete *result, char *input,
								char **path, char **transform)
{
	if (input == NULL || *input == '\0')
	{
		*transform = ft_strdup("./");
		*path = extract_path(*transform);
	}
	else if (input != NULL && *input != '/')
	{
		*transform = ft_strjoin("./", input);
		*path = extract_path(*transform);
		result->index += ft_strlen(*path) - 2;
	}
	else
	{
		*transform = ft_strdup(input);
		*path = extract_path(*transform);
		result->index += ft_strlen(*path);
	}
}

void			get_completion_file(char *input, t_autocomplete *result,
									t_registry *shell)
{
	char	*path;
	char	*transform;
	DIR		*dir;

	(void)shell;
	path = NULL;
	transform = NULL;
	get_path_and_transform(result, input, &path, &transform);
	if ((dir = opendir(transform)) != NULL)
	{
		ft_strdel(&path);
		path = ft_strdup(transform);
		get_file_list(path, transform, result, dir);
		closedir(dir);
	}
	else if ((dir = opendir(path)) != NULL)
	{
		get_file_list(path, transform, result, dir);
		closedir(dir);
	}
	ft_strdel(&path);
	ft_strdel(&transform);
}
