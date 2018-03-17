/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:59:33 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:47 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop_hook(t_fdf *fdf)
{
	if ((fdf->disco == 1) && (fdf->colormap == 1))
	{
		fdf->tick += 1;
		if ((fdf->tick % 5003 == 0) || (fdf->tick % 10007 == 0))
		{
			fdf->pal_i += 1;
			make_palette(fdf);
			redraw(fdf);
		}
		if ((fdf->tick % 20011 == 0))
		{
			fdf->pal_j += 1;
			make_palette(fdf);
			redraw(fdf);
			fdf->tick = 0;
		}
	}
	return (0);
}
