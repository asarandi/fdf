/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:34:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:57:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_mini_calc(int *i1, int *i2, int *i3, int *i4)
{
	if (*i1 > 0)
	{
		(*i2) += *i3;
		(*i1) -= 2 * (*i4);
	}
}

void	plot_line_low(t_fdf *fdf, t_line line, int dx, int dy)
{
	int yi;
	int	d;
	int	y;
	int	x;

	dx = line.d.x - line.o.x;
	dy = line.d.y - line.o.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = line.o.y;
	x = line.o.x;
	while (x < line.d.x)
	{
		(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, x_grad(line, x));
		(void)plot_mini_calc(&d, &y, &yi, &dx);
		d += 2 * dy;
		x++;
	}
	return ;
}

void	plot_line_high(t_fdf *fdf, t_line line, int dx, int dy)
{
	int	xi;
	int	d;
	int	y;
	int	x;

	dx = line.d.x - line.o.x;
	dy = line.d.y - line.o.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	y = line.o.y;
	x = line.o.x;
	while (y < line.d.y)
	{
		(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, y_grad(line, y));
		(void)plot_mini_calc(&d, &x, &xi, &dy);
		d += 2 * dx;
		y++;
	}
	return ;
}

void	plot_line(t_fdf *fdf, t_line line)
{
	t_coord	tmp;

	if (ABS(line.d.y - line.o.y) < ABS(line.d.x - line.o.x))
	{
		if (line.o.x >= line.d.x)
		{
			tmp = line.o;
			line.o = line.d;
			line.d = tmp;
		}
		return (plot_line_low(fdf, line, 0, 0));
	}
	else
	{
		if (line.o.y > line.d.y)
		{
			tmp = line.o;
			line.o = line.d;
			line.d = tmp;
		}
		return (plot_line_high(fdf, line, 0, 0));
	}
	return ;
}
