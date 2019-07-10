/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:02:35 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

uint8_t			protect_no_input(char **av)
{
	if (av == NULL || av[0] == NULL)
	{
		ft_dprintf(2, "%s%s", HASH_GENERAL_ERROR, HASH_NO_AV);
		return (TRUE);
	}
	return (FALSE);
}

void			hash_builtin(t_registry *shell)
{
	ft_hmap_insert(&(shell->hash.blt), "echo", echo_blt);
	ft_hmap_insert(&(shell->hash.blt), "cd", cd_blt);
	ft_hmap_insert(&(shell->hash.blt), "hash", hash_blt);
	ft_hmap_insert(&(shell->hash.blt), "exit", exit_blt);
	ft_hmap_insert(&(shell->hash.blt), "type", type_blt);
	ft_hmap_insert(&(shell->hash.blt), "export", export_blt);
	ft_hmap_insert(&(shell->hash.blt), "set", set_blt);
	ft_hmap_insert(&(shell->hash.blt), "unset", unset_blt);
	ft_hmap_insert(&(shell->hash.blt), "pwd", pwd_blt);
	ft_hmap_insert(&(shell->hash.blt), "fc", fc_blt);
	ft_hmap_insert(&(shell->hash.blt), "fg", fg_blt);
	ft_hmap_insert(&(shell->hash.blt), "bg", bg_blt);
	ft_hmap_insert(&(shell->hash.blt), "jobs", jobs_blt);
	ft_hmap_insert(&(shell->hash.blt), "test", test_blt);
}

int8_t			hash_one(char *key, char *path)
{
	int		ret;

	if ((ret = ft_hmap_insert(&(g_shell->hash.bin), key, path)) == FALSE)
		return (ERROR);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			hash_args(t_list *intern, char *key)
{
	int8_t	ret;
	char	*pathname;

	pathname = NULL;
	if (ft_hmap_getdata(&g_shell->hash.blt, key) != NULL)
		return (0);
	if ((ret = find_in_path(intern, key, &pathname)) == SUCCESS)
	{
		ret = hash_one(key, pathname);
		if (ret == FAILURE || ret == ERROR)
			ft_strdel(&pathname);
	}
	return (ret);
}

uint8_t			hash_print_help(void)
{
	if (write(1, NULL, 0) == FAILURE)
	{
		ft_putendl_fd("42sh: hash: write error: Bad file descriptor", 2);
		return (FALSE);
	}
	ft_printf("%s%s%s%s%s%s%s%s%s%s%s"
			, HASH_USAGE
			, HASH_HELP
			, HASH_H_WIPE
			, HASH_H_ALL
			, HASH_H_HELP
			, HASH_ORULE_1
			, HASH_ORULE_2
			, HASH_OPT_1
			, HASH_OPT_2
			, HASH_UTIL_1
			, HASH_UTIL_2);
	return (TRUE);
}
