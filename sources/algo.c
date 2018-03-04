/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

static void	find_minwidth(t_antfarm *farm, t_ad *d, size_t curstep)
{
	size_t	i;

	d->minwidthlevel = farm->max_width;
	i = -1;
	while (++i < farm->rooms->size)
		if (farm->rooms->vertexes[0][i] && !farm->busy_vertexes[curstep][i])
			if (d->minwidthlevel > farm->width_level[i] ||
				(d->minwidthlevel == farm->width_level[i] &&
					farm->loadness[d->index] > farm->loadness[d->index]))
			{
				d->minwidthlevel = farm->width_level[i];
				d->index = i;
			}
}

static void	fill_path(t_antfarm *farm, t_ad *d, size_t curstep)
{
	size_t		i;

	farm->path->len = 0;
	d->curwidth = d->minwidthlevel;
	farm->path->vertexes[farm->path->len++] = d->index;
	while (d->curwidth > 0)
	{
		d->min_load = -1;
		i = -1;
		while (++i < farm->rooms->size)
			if (farm->rooms->vertexes[farm->path->vertexes[farm->path->len -
				1]][i] && !farm->busy_vertexes[curstep + farm->path->len][i] &&
				farm->width_level[i] == d->curwidth - 1)
			{
				if (d->min_load < 0 || d->min_load > farm->loadness[i])
				{
					d->min_load = farm->loadness[i];
					d->index = i;
				}
			}
		farm->path->vertexes[farm->path->len++] = d->index;
		d->curwidth--;
	}
}

static int	find_da_wei(t_antfarm *farm, size_t curstep,
									int antsleft, _Bool search_optimal)
{
	static int	sleep = 0;
	int			i;
	t_ad		d;

	if (sleep-- > 0)
		return (0);
	fill_loadness(farm, farm->busy_vertexes[curstep]);
	find_minwidth(farm, &d, curstep);
	if (!search_optimal)
		return (d.minwidthlevel + 1);
	i = 1;
	d.diff = d.minwidthlevel - farm->len_of_shortest_path - antsleft;
	if (d.diff >= 0 && search_optimal)
		while (i < d.diff + 2 &&
			curstep + i + 1 < farm->len_of_shortest_path + farm->num_of_ants)
			{
				if (d.minwidthlevel + 1 -
					find_da_wei(farm, curstep + i, antsleft, 0) - i >= antsleft)
				{
					sleep = i - 1;
					return (0);
				}
				i++;
			}
	fill_path(farm, &d, curstep);
	return (farm->path->len);
}

void		algo(t_antfarm *farm)
{
	size_t	curstep;
	size_t	antsleft;
	size_t	i;

	algo_mallocs(farm);
	algo_mallocs2(farm);
	curstep = 0;
	antsleft = farm->num_of_ants;
	while (antsleft > 0)
	{
		i = -1;
		while (++i < farm->max_ant_per_step && antsleft)
			if (!find_da_wei(farm, curstep, antsleft, 1))
				break;
			else
			{
				pave_da_wei(farm, curstep, antsleft);
				antsleft--;
			}
		curstep++;
	}
	farm->total_steps = max(farm->total_steps, curstep + farm->path->len);
}
