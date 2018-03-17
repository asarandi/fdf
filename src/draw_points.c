/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:50:06 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 19:01:37 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_points_norme(int i, int j, t_line ln, t_fdf *fdf)
{
	ln.o.y = fdf->o.y + ((fdf->unit / fdf->tilt) * i);
	ln.o.y -= (fdf->matrix[i * fdf->columns + j]) * fdf->bump;
	ln.o.color = fdf->colors[i * fdf->columns + j];
	mlx_pixel_put(fdf->mlx, fdf->win, ln.o.x, ln.o.y, ln.o.color);
	ln.d.y = fdf->o.y + ((fdf->unit / fdf->tilt) * i);
	ln.d.y -= (fdf->matrix[i * fdf->columns + j + 1]) * fdf->bump;
	ln.d.color = fdf->colors[i * fdf->columns + j + 1];
	if (j + 1 >= fdf->columns - 1)
		mlx_pixel_put(fdf->mlx, fdf->win, ln.d.x, ln.d.y, ln.d.color);
	return ;
}

void	draw_points(t_fdf *fdf)
{
	t_line	ln;
	int		i;
	int		j;
	t_coord	c;

	i = 0;
	c.x = fdf->o.x;
	c.y = fdf->o.y;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns - 1)
		{
			ln.o = c;
			ln.d.x = c.x + (fdf->unit * fdf->mirror);
			draw_points_norme(i, j, ln, fdf);
			c = ln.d;
			j++;
		}
		i++;
		c.x = fdf->o.x - ((fdf->unit / fdf->tilt) * i);
	}
	display_info(fdf);
	return ;
}
