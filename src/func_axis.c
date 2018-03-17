/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_axis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:52:13 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:13:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_x_axis(t_fdf *fdf)
{
	t_line	line;

	line.o.color = COLOR_RED;
	line.d.color = COLOR_WHITE;
	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x + AXIS_LENGTH;
	line.d.y = fdf->o.y;
	plot_line(fdf, line);
	return ;
}

void	draw_y_axis(t_fdf *fdf)
{
	t_line	line;

	line.o.color = COLOR_GREEN;
	line.d.color = COLOR_WHITE;
	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x - (AXIS_LENGTH / fdf->tilt);
	line.d.y = fdf->o.y + (AXIS_LENGTH / fdf->tilt);
	plot_line(fdf, line);
	return ;
}

void	draw_z_axis(t_fdf *fdf)
{
	t_line	line;

	line.o.color = COLOR_BLUE;
	line.d.color = COLOR_WHITE;
	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x;
	line.d.y = fdf->o.y - AXIS_LENGTH;
	plot_line(fdf, line);
	return ;
}
