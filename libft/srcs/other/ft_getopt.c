/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 03:15:30 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 00:16:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		push_back(char *to_push)
{
	char	holder;

	if (!to_push)
		return (1);
	while (to_push[1])
	{
		holder = to_push[0];
		to_push[0] = to_push[1];
		to_push[1] = holder;
		to_push++;
	}
	return (0);
}

static char		parser(int ac, char **av, const char *optstr, char **opt)
{
	static int	lvl = 1;
	int			flag;
	int			i;
	char		error;

	if (!opt || lvl == ac || !ft_strncmp(av[lvl], "--", 3) || av[lvl][0] != '-')
		return (1);
	i = 1;
	flag = 1;
	while (av[lvl][i] != '\0' && flag)
	{
		error = av[lvl][i];
		flag = av[lvl][i] != '-' && ft_strchr(optstr, av[lvl][i]) ? 1 : 0;
		if (flag && push_back(ft_strchr(*opt, av[lvl][i])))
			if (!(*opt = ft_strinsert(opt, av[lvl][i], ft_strlen(*opt))))
				flag = 0;
		i++;
	}
	lvl++;
	if (flag == 1 && (error = parser(ac, av, optstr, opt)) == 1)
		return (1);
	ft_strdel(opt);
	return (error);
}

int				ft_getopt(int ac, char **av, const char *optstr)
{
	static t_opt_buffer	opt = {.buffer = NULL, .index = 0};
	int					error;

	if (ac == 1 || av == NULL || optstr == NULL)
		return (0);
	if (!opt.buffer && av[1][0] == '-')
	{
		opt.buffer = ft_strnew(0);
		if ((error = parser(ac, av, optstr, &opt.buffer)) != 1)
			return (-error);
	}
	if (opt.buffer && opt.buffer[opt.index])
		return ((int)opt.buffer[(++opt.index) - 1]);
	else if (opt.buffer)
		ft_strdel(&opt.buffer);
	return (-1);
}
