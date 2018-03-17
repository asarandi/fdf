/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:01:42 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 18:34:21 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	palette_redraw(t_fdf *fdf, int *index)
{
	if (fdf->colormap == 1)
	{
		(*index) += 1;
		make_palette(fdf);
		redraw(fdf);
	}
	return ;
}

void	color_swap(t_fdf *fdf)
{
	int	*ptr;

	ptr = fdf->colors;
	fdf->colors = fdf->colors2;
	fdf->colors2 = ptr;
	return ;
}

void	alternate_colors(t_fdf *fdf)
{
	color_swap(fdf);
	fdf->colormap ^= 1;
	redraw(fdf);
	return ;
}
