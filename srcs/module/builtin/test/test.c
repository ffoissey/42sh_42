/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			load_test_hashmap(t_hash *callbacks)
{
	ft_hmap_insert(callbacks, "-b", test_b_cb);
	ft_hmap_insert(callbacks, "-c", test_c_cb);
	ft_hmap_insert(callbacks, "-d", test_d_cb);
	ft_hmap_insert(callbacks, "-e", test_e_cb);
	ft_hmap_insert(callbacks, "-f", test_f_cb);
	ft_hmap_insert(callbacks, "-g", test_g_cb);
	ft_hmap_insert(callbacks, "-L", test_caps_l_cb);
	ft_hmap_insert(callbacks, "-p", test_p_cb);
	ft_hmap_insert(callbacks, "-r", test_r_cb);
	ft_hmap_insert(callbacks, "-S", test_caps_s_cb);
	ft_hmap_insert(callbacks, "-s", test_s_cb);
	ft_hmap_insert(callbacks, "-u", test_u_cb);
	ft_hmap_insert(callbacks, "-w", test_w_cb);
	ft_hmap_insert(callbacks, "-x", test_x_cb);
	ft_hmap_insert(callbacks, "-z", test_z_cb);
	ft_hmap_insert(callbacks, "=", test_equal_cb);
	ft_hmap_insert(callbacks, "!=", test_diff_cb);
	ft_hmap_insert(callbacks, "-eq", test_eq_cb);
	ft_hmap_insert(callbacks, "-ne", test_ne_cb);
	ft_hmap_insert(callbacks, "-gt", test_gt_cb);
	ft_hmap_insert(callbacks, "-ge", test_ge_cb);
	ft_hmap_insert(callbacks, "-lt", test_lt_cb);
	ft_hmap_insert(callbacks, "-le", test_le_cb);
}

static uint8_t		handle_input(t_hash *callbacks, int ac, char **av, int i)
{
	uint8_t		status;

	if (ac == 1)
		status = test_single_arg(av[i]);
	else if (ac == 2)
		status = two_arg_input(callbacks, av + i);
	else if (ac == 3)
		status = three_arg_input(callbacks, av + i);
	else
	{
		ft_dprintf(2, "42sh: test: Too many arguments\n");
		status = ERROR;
	}
	return (status);
}

static uint8_t		check_no_input(t_hash *callbacks, int ac)
{
	if (ac == 0)
	{
		ft_hmap_free_content(callbacks, NULL);
		free(callbacks->map);
		return (TRUE);
	}
	return (FALSE);
}

int8_t				test_blt(t_list *intern, char **av)
{
	int				i;
	int				ac;
	uint8_t			status;
	t_hash			callbacks;

	(void)intern;
	ft_bzero(&callbacks, sizeof(t_hash));
	callbacks = ft_hmap_init(TEST_HASH_SIZE);
	load_test_hashmap(&callbacks);
	ac = ft_tabsize(av);
	i = 1 + (ac > 2 && ft_strequ(av[1], "!"));
	ac -= i;
	if (check_no_input(&callbacks, ac) == TRUE)
		return (EXIT_FALSE);
	status = handle_input(&callbacks, ac, av, i);
	if (i > 1 && ac >= 1 && status != ERROR)
		status = test_not(status);
	ft_hmap_free_content(&callbacks, NULL);
	free(callbacks.map);
	if (status == FALSE)
		return (EXIT_FALSE);
	else if (status == TRUE)
		return (EXIT_TRUE);
	return (ERROR);
}
