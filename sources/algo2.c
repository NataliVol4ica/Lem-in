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

#include "lemin.h"

void	fill_loadness(t_antfarm *farm, _Bool *busy_vertexes)
{
	int		curwidth;
	size_t	i;
	size_t	j;

	farm->loadness[0] = 1;
	farm->loadness[1] = 0;
	curwidth = farm->max_width - 1;
	while (curwidth > 0)
	{
		i = -1;
		while (++i < farm->rooms->size)
			if (farm->width_level[i] == curwidth && !busy_vertexes[i])
			{
				farm->loadness[i] = 0;
				j = -1;
				while (++j < farm->rooms->size)
					if (!busy_vertexes[j] && farm->rooms->vertexes[i][j] &&
						(farm->width_level[j] == curwidth + 1 || j == 0))
						farm->loadness[i] += farm->loadness[j];
			}
		curwidth--;
	}
}

void	pave_da_wei(t_antfarm *farm, size_t step, size_t antsleft)
{
	int	i;

	i = -1;
	while (++i < farm->path->len)
	{
		farm->steps[step + i][farm->num_of_ants - antsleft] =
											farm->path->vertexes[i];
		if (farm->path->vertexes[i] != 1)
			farm->busy_vertexes[step + i][farm->path->vertexes[i]] = 1;
	}
}
