/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:04:43 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:13:02 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_matrix(t_fdf *fdf)
{
	if (fdf->points == 1)
		draw_points(fdf);
	else
		draw_lines(fdf);
	return ;
}

void	redraw(t_fdf *fdf)
{
	(void)mlx_clear_window(fdf->mlx, fdf->win);
	draw_matrix(fdf);
	return ;
}
