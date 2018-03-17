/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:52:13 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 18:51:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook_extra(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_M)
	{
		fdf->mirror = -(fdf->mirror);
		calc_position(fdf);
		if (fdf->mirror < 0)
		{
			fdf->o.x -= fdf->y_area;
			fdf->o.x += fdf->x_area;
		}
		if (fdf->mirror > 0)
		{
			fdf->o.x += fdf->y_area;
			fdf->o.x -= fdf->x_area;
		}
		redraw(fdf);
	}
	if (keycode == KEY_ESCAPE)
	{
		(void)mlx_destroy_window(fdf->mlx, fdf->win);
		(void)clean_up(fdf);
		exit(0);
	}
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_4)
		draw_x_axis(fdf);
	if (keycode == KEY_5)
		draw_y_axis(fdf);
	if (keycode == KEY_6)
		draw_z_axis(fdf);
	if ((keycode == KEY_D) && (fdf->colormap == 1))
		fdf->disco ^= 1;
	if (keycode == KEY_C)
		alternate_colors(fdf);
	if (keycode == KEY_H)
	{
		fdf->help ^= 1;
		redraw(fdf);
	}
	if (keycode == KEY_P)
	{
		fdf->points ^= 1;
		redraw(fdf);
	}
	return (key_hook_extra(keycode, fdf));
}
