/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:41:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:39 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		count_words_per_line(char *str)
{
	char	**split;
	int		count;

	split = ft_strsplit(str, INT_SEPARATOR);
	count = 0;
	while (split[count] != NULL)
	{
		free(split[count]);
		count += 1;
	}
	free(split);
	return (count);
}

int		hexa_to_int(char *str)
{
	int	i;
	int	r;

	str = ft_strtolower(str);
	if ((ft_isdigit(str[0])) && (str[1] != 'x'))
		return (ft_atoi(str));
	if ((str[0] != '0') || (str[1] != 'x'))
		return (COLOR_WHITE);
	r = 0;
	i = 2;
	while (str[i])
	{
		r = r << 4;
		if (ft_isdigit(str[i]))
			r += (str[i] - '0');
		else if ((str[i] >= 'a') && (str[i] <= 'f'))
			r += (10 + (str[i] - 'a'));
		else
			break ;
		i++;
	}
	return (r);
}

void	parse_line_of_ints(t_fdf *fdf, int *i, char *line)
{
	char	**split;
	char	*ptr;
	int		k;

	split = ft_strsplit(line, INT_SEPARATOR);
	k = 0;
	while (split[k] != NULL)
	{
		if ((ptr = ft_strchr(split[k], COLOR_SEPARATOR)) != NULL)
			fdf->colors[*i] = hexa_to_int(ptr + 1);
		else
			fdf->colors[*i] = DEFAULT_COLOR;
		fdf->matrix[*i] = ft_atoi(split[k]);
		if (fdf->matrix[*i] > fdf->highest)
			fdf->highest = fdf->matrix[*i];
		if (fdf->matrix[*i] < fdf->lowest)
			fdf->lowest = fdf->matrix[*i];
		(*i)++;
		free(split[k++]);
	}
	free(split);
	return ;
}
