/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_repeat_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:53:13 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 18:36:49 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_repeat_extra(int keycode, t_fdf *fdf)
{
	static int	tmp;

	if ((keycode == KEY_V) && (fdf->colormap == 1))
	{
		fdf->disco = 0;
		fdf->pal_i = tmp++;
		height_palette(fdf);
		redraw(fdf);
	}
	if (keycode == KEY_UP)
		move_on_y_axis(fdf, fdf->move_unit);
	if (keycode == KEY_DOWN)
		move_on_y_axis(fdf, -fdf->move_unit);
	if (keycode == KEY_RIGHT)
		move_on_x_axis(fdf, -fdf->move_unit);
	if (keycode == KEY_LEFT)
		move_on_x_axis(fdf, fdf->move_unit);
	return (0);
}

int	key_repeat(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_I)
		zoom_redraw(fdf, (double)ZOOM_INCREMENT);
	if (keycode == KEY_O)
		zoom_redraw(fdf, (double)-ZOOM_INCREMENT);
	if (keycode == KEY_J)
		bump_redraw(fdf, (double)fdf->alt_increment);
	if (keycode == KEY_K)
		bump_redraw(fdf, (double)-fdf->alt_increment);
	if (keycode == KEY_T)
		tilt_redraw(fdf, (double)TILT_INCREMENT);
	if (keycode == KEY_Y)
		tilt_redraw(fdf, (double)-TILT_INCREMENT);
	if (keycode == KEY_Z)
		palette_redraw(fdf, &(fdf->pal_i));
	if (keycode == KEY_X)
		palette_redraw(fdf, &(fdf->pal_j));
	return (key_repeat_extra(keycode, fdf));
}
