/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_filler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:47 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:47 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

#include <stdlib.h>

static void	wnum_norm(t_antfarm *farm, int *num_of_used,
											int *windex, _Bool *is_used)
{
	size_t	i;
	size_t	j;
	size_t	min;

	min = 0;
	i = -1;
	while (++i < farm->rooms->size)
		if (is_used[i] && farm->width_level[i] == *windex)
		{
			j = -1;
			while (++j < farm->rooms->size)
				if (!is_used[j] && farm->rooms->vertexes[i][j])
				{
					farm->width_level[j] = *windex + 1;
					is_used[j] = 1;
					if (j == 0)
						farm->len_of_shortest_path = *windex + 1;
					*num_of_used = *num_of_used - 1;
					min++;
				}
		}
	if (min < farm->max_ant_per_step && farm->len_of_shortest_path < 0)
		farm->max_ant_per_step = min;
	*windex = *windex + 1;	
}

void		width_numeration(t_antfarm *farm)
{
	_Bool	is_used[farm->rooms->size];
	int		windex;
	size_t	i;
	int		num_of_used;

	if (!(farm->width_level = (int*)malloc(sizeof(int) * farm->rooms->size)))
		mall_error();
	i = -1;
	while (++i < farm->rooms->size)
		is_used[i] = 0;
	is_used[1] = 1;
	farm->width_level[1] = 0;
	farm->max_ant_per_step = farm->rooms->size;
	farm->len_of_shortest_path = -1;
	num_of_used = farm->rooms->size - 1;
	while (num_of_used)
		wnum_norm(farm, &num_of_used, &windex, is_used);
	windex++;
	farm->max_width = windex;
	farm->width_level[0] = windex;
}
