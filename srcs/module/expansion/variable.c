/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	*variable_replace(t_list *lst, t_vector *str, uint32_t start_idx)
{
	uint32_t	i;
	char		*sub;
	char		*data;
	char		*data_name;

	sub = ft_strsub(vct_get_string(str), start_idx + 1
			, vct_len(str) - (start_idx + 1));
	i = 0;
	while (sub[i] && (ft_isalnum(sub[i]) || sub[i] == '_'))
	{
		if (i == 0 && ft_isdigit(sub[i]))
			break ;
		i++;
	}
	data_name = ft_strsub(sub, 0, i);
	data = get_var(lst, data_name);
	ft_strdel(&sub);
	ft_strdel(&data_name);
	if (data == NULL)
		data = "";
	vct_replace_string(str, start_idx, start_idx + i + 1, data);
	sub = ft_strdup(vct_get_string(str));
	return (sub);
}

static int	variable_concat(t_list *lst, char **dest, int i)
{
	t_vector	*vector;

	vector = vct_dups(*dest);
	ft_strdel(dest);
	if ((*dest = variable_replace(lst, vector, i)) == NULL)
		return (-1);
	vct_del(&vector);
	return (1);
}

static int	variable_special(t_list *intern, char **dest, int i)
{
	t_vector	*vector;
	char		*expanded;

	expanded = NULL;
	vector = vct_dups(*dest);
	if ((*dest)[i + 1] == '0')
		expanded = get_var(intern, "0");
	else if ((*dest)[i + 1] == '$')
		expanded = get_var(intern, "$");
	else if ((*dest)[i + 1] == '-')
		expanded = get_var(intern, "-");
	else if ((*dest)[i + 1] == '!')
		expanded = get_var(intern, "!");
	else
		expanded = get_var(intern, "?");
	ft_strdel(dest);
	if (expanded)
		vct_replace_string(vector, i, i + 2, expanded);
	else
		vct_replace_string(vector, i, i + 2, "");
	*dest = ft_strdup(vct_get_string(vector));
	vct_del(&vector);
	return (1);
}

static int	check_expansion(char **dest, uint32_t *i, t_quote quote)
{
	int		check;

	check = 0;
	if ((*dest)[*i] != '$' || quote == QUOTE_SINGLE)
		return (0);
	if ((*dest)[*i + 1] == '{')
		check = parameter_expansion(g_shell->intern, dest, *i);
	else if (ft_strnequ((*dest) + *i + 1, "((", 2))
		check = 0;
	else if (ft_strnequ((*dest) + *i + 1, "(", 1))
	{
		ft_dprintf(2, "42sh: bad substitution\n");
		check = -1;
	}
	else if (ft_strchr(EXP_SPECIAL, (*dest)[*i + 1]))
		check = variable_special(g_shell->intern, dest, *i);
	else if ((*dest)[*i + 1] != '\0')
	{
		if (ft_strchr(EXP_CHECK, (*dest)[*i + 1]))
			check = 0;
		else if (quote != QUOTE_SINGLE)
			check = variable_concat(g_shell->intern, dest, *i);
	}
	return (check);
}

char		*variable_expansion(t_list *intern_var, char *str)
{
	uint32_t	i;
	uint32_t	len;
	t_quote		quote;
	char		*dest;
	int			result;

	i = 0;
	quote = 0;
	dest = ft_strdup(str);
	len = ft_strlen(dest);
	(void)intern_var;
	while (dest != NULL && i < len && dest[i] != '\0' && (result = 0) == 0)
	{
		if (ft_strchr("\'\"", dest[i]))
			quote = select_quoting(quote, dest[i]);
		if (dest[i] == '\\' && (quote == QUOTE_OFF || quote == QUOTE_DOUBLE))
			i = check_backslash(dest, quote, i);
		else if ((result = check_expansion(&dest, &i, quote)) == 1)
			len = ft_strlen(dest);
		else if (result == -1)
			ft_strdel(&dest);
		i += result == 0 ? 1 : 0;
	}
	return (dest);
}
