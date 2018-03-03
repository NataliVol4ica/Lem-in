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

void	optimization_mallocs(t_antfarm *farm)
{
	size_t	i;

	if (!(farm->is_new_graph_vertex =
		(_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->is_wd_chain_vertex =
		(_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->is_vertex_visited =
		(_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->wd_search_arr =
		(int*)malloc(sizeof(int) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->old_to_new = (int*)malloc(sizeof(int) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->new_to_old = (int*)malloc(sizeof(int) * farm->num_of_rooms)))
		mall_error();
	i = -1;
	while (++i < farm->num_of_rooms)
	{
		farm->is_new_graph_vertex[i] = 0;
		farm->is_wd_chain_vertex[i] = 0;
		farm->is_vertex_visited[i] = 0;
	}
}

void	new_graph_mallocs(t_antfarm *farm)
{
	size_t	i;

	if (!(farm->rooms->vertexes = (_Bool**)malloc(sizeof(_Bool*) *
									farm->rooms->size)))
		mall_error();
	i = -1;
	while (++i < farm->rooms->size)
		if (!(farm->rooms->vertexes[i] = (_Bool*)malloc(sizeof(_Bool) *
										farm->rooms->size)))
			mall_error();
}

void	algo_mallocs(t_antfarm *farm)
{
	size_t	i;
	size_t	j;

	if (!(farm->loadness = (int*)malloc(sizeof(int) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->steps = (int**)malloc(sizeof(int*) * 
					(farm->len_of_shortest_path + farm->num_of_ants))))
		mall_error();
	if (!(farm->busy_vertexes = (_Bool**)malloc(sizeof(_Bool*) *
					(farm->len_of_shortest_path + farm->num_of_ants))))
		mall_error();
	i = -1;
	while (++i < farm->len_of_shortest_path + farm->num_of_ants && (j = -1))
	{
		if (!(farm->steps[i] = (int*)malloc(sizeof(int) * farm->num_of_ants)))
			mall_error();
		if (!(farm->busy_vertexes[i] = (_Bool*)malloc(sizeof(_Bool) *
										farm->num_of_ants)))
			mall_error();
		while (++j < farm->num_of_ants)
		{
			farm->steps[i][j] = -1;
			farm->busy_vertexes[i][j] = 0;
		}
	}
}

void	algo_mallocs2(t_antfarm *farm)
{
	if (!(farm->path = (t_path*)malloc(sizeof(t_path))))
		mall_error();
	if (!(farm->path->vertexes = (int*)malloc(sizeof(int) * farm->num_of_rooms)))
		mall_error();
}
