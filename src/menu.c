/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:32:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:56:56 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_help(t_fdf *fdf, int i, int j)
{
	char		buf[50];
	char		*ptr;
	const char	*str[] = {INFO_1, INFO_2, INFO_3, INFO_4, INFO_5, INFO_6,
		INFO_7, INFO_8, INFO_9, INFO_10, INFO_11, INFO_12};

	ptr = ft_strjoin("tilt ", ftoa(&buf[0], fdf->tilt));
	mlx_string_put(fdf->mlx, fdf->win, 10, 50, TEXT_COLOR, ptr);
	free(ptr);
	ptr = ft_strjoin("unit ", ftoa(&buf[0], fdf->unit));
	mlx_string_put(fdf->mlx, fdf->win, 10, 65, TEXT_COLOR, ptr);
	free(ptr);
	ptr = ft_strjoin("bump ", ftoa(&buf[0], fdf->bump));
	mlx_string_put(fdf->mlx, fdf->win, 10, 80, TEXT_COLOR, ptr);
	free(ptr);
	while (i < 12)
	{
		mlx_string_put(fdf->mlx, fdf->win, 10, j,
				TEXT_COLOR, (char *)str[i++]);
		j += 15;
	}
}

void	display_info(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 10, 20, TEXT_COLOR,
			"press [h] for help/info");
	if (fdf->help)
		show_help(fdf, 0, 110);
	return ;
}
