/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_coords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:03:10 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:13:22 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_position(t_fdf *fdf)
{
	int	u;

	u = (int)fdf->unit;
	fdf->x_area = (((fdf->columns - 1) * u) + ((fdf->rows - 1) * u));
	fdf->y_area = u * (fdf->rows - 1);
	return ;
}

void	calc_unit_size(t_fdf *fdf)
{
	int	tmp1;
	int	tmp2;
	int max_x;
	int max_y;

	tmp1 = ((WIDTH) / 10) * 9;
	tmp2 = ((fdf->columns - 1) * 2) + (fdf->rows - 1);
	max_x = tmp1 / tmp2;
	tmp1 = ((HEIGHT) / 10) * 9;
	tmp2 = (fdf->rows - 1);
	max_y = tmp1 / tmp2;
	if (max_y < max_x)
		max_x = max_y;
	max_x -= (max_x % 2);
	if (max_x < 1)
		max_x = 1;
	fdf->unit = (double)(max_x * 2);
	fdf->x_area = max_x * (((fdf->columns - 1) * 2) + (fdf->rows - 1));
	fdf->y_area = max_x * (fdf->rows - 1);
	fdf->o.x = (WIDTH - fdf->x_area) / 2;
	fdf->o.x += fdf->y_area;
	fdf->o.y = (HEIGHT - fdf->y_area) / 2;
	return ;
}

void	init_coordinates(t_fdf *fdf)
{
	calc_unit_size(fdf);
	ft_printf("unit size is %f\n", fdf->unit);
	ft_printf("highest = %d\n", fdf->highest);
	ft_printf("lowest = %d\n", fdf->lowest);
	ft_printf("rows = %d, columns = %d\n", fdf->rows, fdf->columns);
	fdf->alt_increment = (double)fdf->unit / 20;
	fdf->bump = fdf->alt_increment;
	fdf->tilt = 2.0;
	fdf->mirror = 1.0;
	fdf->pal_i = 2;
	fdf->pal_j = 9;
	height_map(fdf);
	color_swap(fdf);
	make_palette(fdf);
	color_swap(fdf);
	fdf->move_unit = HEIGHT / 20;
	return ;
}
