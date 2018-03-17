/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:06:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:22 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		return (show_usage());
	if ((fdf = ft_memalloc(sizeof(t_fdf))) == NULL)
		fatal_error("ft_memalloc() failed");
	fdf->file = av[1];
	(void)read_matrix(fdf);
	(void)init_coordinates(fdf);
	if ((fdf->mlx = mlx_init()) == NULL)
		fatal_error("mlx_init() failed");
	mlx_do_key_autorepeaton(fdf->mlx);
	if ((fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, TITLE)) == NULL)
		fatal_error("mlx_new_window() failed");
	(void)mlx_hook(fdf->win, KEYPRESS, KEYPRESSMASK, key_repeat, fdf);
	(void)mlx_key_hook(fdf->win, key_hook, fdf);
	(void)mlx_mouse_hook(fdf->win, mouse_hook, fdf);
	(void)mlx_expose_hook(fdf->win, expose_hook, fdf);
	(void)mlx_loop_hook(fdf->mlx, loop_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
