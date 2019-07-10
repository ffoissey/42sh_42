/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		p_insert_missing(t_sle *sle, t_vector *text, uint64_t index)
{
	if (sle->prompt.missing_char != NULL)
		vct_replace_string(text, index, index + 2,
						sle->prompt.missing_char);
}

void		p_insert_name(t_vector *text, uint64_t index)
{
	vct_replace_string(text, index, index + 2, "42sh");
}

void		p_insert_username(t_sle *sle, t_vector *text, uint64_t index)
{
	char	*username;

	username = vct_get_string(sle->interns.username);
	username = ft_strdup(username == NULL ? "user" : username);
	vct_replace_string(text, index, index + 2, username);
	ft_strdel(&username);
}

void		p_insert_cwd(t_sle *sle, t_vector *text, uint64_t index)
{
	size_t	len;
	char	*cwd;
	char	*home;

	cwd = vct_get_string(sle->interns.pwd);
	home = vct_get_string(sle->interns.home);
	vct_replace_string(text, index, index + 2, cwd);
	if (ft_strbeginswith(cwd, home))
	{
		len = ft_strlen(home);
		vct_replace_string(text, index, index + len, "~");
	}
}

void		p_insert_host(t_vector *text, uint64_t index)
{
	char	*host;
	char	*hostname;
	size_t	host_len;

	host_len = 32;
	host = ft_strnew(host_len);
	if (gethostname(host, host_len) != 0)
		hostname = ft_strdup("hostname");
	else
		hostname = ft_strsub(host, 0, ft_strcspn(host, "."));
	vct_replace_string(text, index, index + 2, hostname);
	ft_strdel(&host);
	ft_strdel(&hostname);
}
