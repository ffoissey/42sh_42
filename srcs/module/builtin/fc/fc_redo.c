/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_redo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:29:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			get_target_and_result(char ***av, char **target,
						char **result)
{
	if (**av == NULL)
		return ;
	*result = ft_strchr(**av, '=');
	if (*result == NULL)
		return ;
	**result = '\0';
	(*result)++;
	(*target) = **av;
	(*av)++;
}

static int8_t		replace_cmd(char **cmd, char *target, char *result)
{
	char	*ptr_target;
	char	*out;
	char	*tmp;

	if (target == NULL || result == NULL || *target == '\0')
		return (FAILURE);
	if (ft_strequ(target, result) == TRUE)
		return (FAILURE);
	ptr_target = ft_strstr(*cmd, target);
	if (ptr_target == NULL)
		return (FAILURE);
	tmp = ft_strdup(*cmd);
	out = ft_strsub(tmp, 0, ptr_target - *cmd);
	ft_strdel(&tmp);
	tmp = ft_strjoin(out, result);
	ft_strdel(&out);
	out = ft_strjoin(tmp, ptr_target + ft_strlen(target));
	ft_strdel(&tmp);
	ft_strdel(cmd);
	*cmd = out;
	return (SUCCESS);
}

static void			free_tools(char **target, char **result, char **param)
{
	ft_strdel(target);
	ft_strdel(result);
	ft_strdel(param);
}

static int8_t		get_cmd(char **av, char **cmd)
{
	char	*target;
	char	*result;
	char	*param;

	target = NULL;
	result = NULL;
	param = NULL;
	get_target_and_result(&av, &target, &result);
	if (*av)
	{
		if (ft_isnumeric(*av) == FALSE)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: fc: history specification out of range\n");
			free_tools(&target, &result, &param);
			return (FAILURE);
		}
		param = ft_strdup(*av);
	}
	*cmd = ft_strdup(history(g_shell, param,
				GET_ENTRY | (param ? BY_ID : PREV)));
	while (replace_cmd(cmd, target, result) == SUCCESS)
		;
	free_tools(&target, &result, &param);
	return (SUCCESS);
}

uint8_t				fc_redo(char **av)
{
	char		*cmd;
	t_vector	*vct_cmd;

	cmd = NULL;
	history(g_shell, NULL, POP_ENTRY);
	if (get_cmd(av, &cmd) == FAILURE)
		return (1);
	if (cmd == NULL)
		return (1);
	if (write(1, NULL, 0) == FAILURE)
	{
		ft_putendl_fd("42sh: fc: write error: Bad file descriptor", 2);
		ft_strdel(&cmd);
		return (1);
	}
	ft_putendl(cmd);
	vct_cmd = vct_dups(cmd);
	if (verif_line(vct_cmd) == TRUE)
		execution_pipeline(g_shell, &vct_cmd);
	vct_del(&vct_cmd);
	ft_strdel(&cmd);
	return (SUCCESS);
}
