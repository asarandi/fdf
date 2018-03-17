/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:47:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_palette_index(int index)
{
	const int	palette[] = {0x001F3F, 0x0074D9, 0x7FDBFF, 0x39CCCC, 0x3D9970,
		0x2ECC40, 0x01FF70, 0xFFDC00, 0xFF851B, 0xFF4136, 0xF012BE, 0xB10DC9,
		0x85144B, 0xFFFFFF, 0xDDDDDD, 0xAAAAAA};
	const int	pal_size = sizeof(palette) / sizeof(int);

	index = index % pal_size;
	return (palette[index]);
}

int		gpi(int index)
{
	const int	palette[] = {0x001F3F, 0x0074D9, 0x7FDBFF, 0x39CCCC, 0x3D9970,
		0x2ECC40, 0x01FF70, 0xFFDC00, 0xFF851B, 0xFF4136, 0xF012BE, 0xB10DC9,
		0x85144B, 0xFFFFFF, 0xDDDDDD, 0xAAAAAA};
	const int	pal_size = sizeof(palette) / sizeof(int);

	index = index % pal_size;
	return (palette[index]);
}

void	make_palette(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns)
		{
			if (fdf->cidx == 0)
				fdf->colors[(i * fdf->columns) + j] = gpi(fdf->pal_i);
			else
				fdf->colors[(i * fdf->columns) + j] = gpi(fdf->pal_j);
			fdf->cidx ^= 1;
			j++;
		}
		if (fdf->columns % 2 == 0)
			fdf->cidx ^= 1;
		i++;
	}
}
