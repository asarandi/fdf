/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:59:03 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, fdf->color);
	if (button == 1)
	{
		fdf->o.x = x;
		fdf->o.y = y;
		redraw(fdf);
	}
	else if (button == 4)
		zoom_redraw(fdf, 1);
	else if (button == 5)
		zoom_redraw(fdf, -1);
	return (0);
}
