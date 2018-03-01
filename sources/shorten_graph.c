/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shorten_graph.c                                    :+:      :+:    :+:   */
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

static void	cutter_depth_search(t_antfarm *farm)
{
	size_t	prev_vertex;
	size_t	i;
	size_t	j;

	prev_vertex = farm->wd_search_arr[farm->depth_level - 1];
	i = -1;
	while (++i < farm->num_of_rooms)
		if (i == prev_vertex || farm->is_vertex_visited[i] ||
								farm->is_wd_chain_vertex[i])
			continue;
		else if (farm->init_rooms->vertexes[prev_vertex][i])
		{
			farm->wd_search_arr[farm->depth_level++] = i;
			farm->is_wd_chain_vertex[i] = 1;
			if (i == 1 && (j = -1))
			{
				while (++j < farm->depth_level)
					farm->is_new_graph_vertex[farm->wd_search_arr[j]] = 1;
				farm->is_vertex_visited[0] = 1;
				farm->depth_level--;
				farm->is_wd_chain_vertex[i] = 0;
				return;
			}
			cutter_depth_search(farm);
			farm->depth_level--;
			farm->is_wd_chain_vertex[i] = 0;
		}
	farm->is_vertex_visited[prev_vertex] = 1;
}

static void	algo_mallocs(t_antfarm *farm)
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

void		optimize_graph(t_antfarm *farm)
{
	size_t	i;
	size_t	j;

	algo_mallocs(farm);
	farm->is_wd_chain_vertex[0] = 1;
	farm->depth_level = 1;
	farm->wd_search_arr[0] = 0;
	farm->rooms->size = 0;
	cutter_depth_search(farm);
	i = -1;
	while (++i < farm->num_of_rooms)
		if (farm->is_new_graph_vertex[i])
		{
			farm->old_to_new[i] = farm->rooms->size;
			farm->new_to_old[farm->rooms->size++] = i;
		}
	if (farm->rooms->size == 0)
		invalid_farm();
	if (!(farm->rooms->vertexes = (_Bool**)malloc(sizeof(_Bool*) * farm->rooms->size)))
		mall_error();
	i = -1;
	while (++i < farm->rooms->size)
		if (!(farm->rooms->vertexes[i] = (_Bool*)malloc(sizeof(_Bool) * farm->rooms->size)))
			mall_error();
	i = -1;
	while (++i < farm->num_of_rooms)
	{
		if (farm->is_new_graph_vertex[i])
		{
			j = -1;
			while (++j < farm->num_of_rooms)
				if (farm->is_new_graph_vertex[j])
				{
					farm->rooms->vertexes[farm->old_to_new[i]][farm->old_to_new[j]] = farm->init_rooms->vertexes[i][j];
					farm->rooms->vertexes[farm->old_to_new[j]][farm->old_to_new[i]] = farm->init_rooms->vertexes[j][i];
				}
		}
	}
	free(farm->is_new_graph_vertex);
	i = -1;
	while (++i < farm->num_of_rooms)
		free(farm->init_rooms->vertexes[i]);
	free(farm->init_rooms->vertexes);
	free(farm->init_rooms);
}
