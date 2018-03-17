/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_heights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:27:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:13:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		int_array_count_unique(int *array, int size)
{
	int	i;
	int	result;
	int	current;

	i = 0;
	current = array[i];
	result = 1;
	while (i < size)
	{
		if (array[i] != current)
		{
			current = array[i];
			result += 1;
		}
		i++;
	}
	return (result);
}

void	int_array_copy_unique(int *dst, int *org, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	dst[j++] = org[i];
	while (i < size)
	{
		if (org[i] != dst[j - 1])
			dst[j++] = org[i];
		i++;
	}
	return ;
}

void	height_map(t_fdf *fdf)
{
	int		*copy;
	int		size;
	size_t	si;

	size = fdf->rows * fdf->columns;
	si = sizeof(int);
	copy = ft_memcpy(ft_memalloc((size + 1) * si), fdf->matrix, size * si);
	copy = merge_sort(copy, size);
	fdf->heights_count = int_array_count_unique(copy, size);
	ft_printf("counted %d unique heights\n", fdf->heights_count);
	fdf->heights = ft_memalloc((fdf->heights_count + 1) * sizeof(int));
	(void)int_array_copy_unique(fdf->heights, copy, size);
	free(copy);
	return ;
}

void	height_palette(t_fdf *fdf)
{
	int	k;
	int	i;
	int	j;

	k = 0;
	while (k < fdf->heights_count)
	{
		i = 0;
		while (i < fdf->rows)
		{
			j = 0;
			while (j < fdf->columns)
			{
				if (fdf->matrix[(i * fdf->columns) + j] == fdf->heights[k])
					fdf->colors[(i * fdf->columns) + j] = gpi(fdf->pal_i);
				j++;
			}
			i++;
		}
		fdf->pal_i++;
		k++;
	}
	return ;
}
