/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:56:32 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:28 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	merge_norme1(int *i, int *j, int *k)
{
	(*i) = 0;
	(*j) = 0;
	(*k) = 0;
}

void	merge_norme2(int size, int *left, int *merged)
{
	int	i;

	i = 0;
	while (i < size)
	{
		left[i] = merged[i];
		i++;
	}
}

int		*merge(int *left, int ln, int *right, int rn)
{
	int i;
	int j;
	int k;
	int	*merged;

	(void)merge_norme1(&i, &j, &k);
	merged = ft_memalloc((ln + rn) * sizeof(int));
	while ((i < ln) && (j < rn))
	{
		if (left[i] <= right[j])
			merged[k++] = left[i++];
		else
			merged[k++] = right[j++];
	}
	while (i < ln)
		merged[k++] = left[i++];
	while (j < rn)
		merged[k++] = right[j++];
	(void)merge_norme2(ln + rn, left, merged);
	free(merged);
	return (left);
}

int		*merge_sort(int *arr, int n)
{
	int ln;
	int rn;

	if (n < 2)
		return (arr);
	ln = n / 2;
	rn = n - ln;
	merge_sort(&arr[0], ln);
	merge_sort(&arr[ln], rn);
	merge(&arr[0], ln, &arr[ln], rn);
	return (arr);
}
