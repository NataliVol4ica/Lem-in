/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to_graph.c                                    :+:      :+:    :+:   */
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

static void	fuck_the_norm(t_antfarm *farm, t_link *link)
{
	t_list	*temp;
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < farm->num_of_rooms)
	{
		if (!(farm->init_rooms->vertexes[i] = (_Bool*)malloc(sizeof(_Bool) *
												farm->num_of_rooms)))
			mall_error();
		j = -1;
		while (++j < farm->num_of_rooms)
			farm->init_rooms->vertexes[i][j] = 0;
	}
	while (farm->link_list)
	{
		temp = farm->link_list->next;
		link = *(t_link**)farm->link_list->content;
		farm->init_rooms->vertexes[link->vertex1][link->vertex2] = 1;
		farm->init_rooms->vertexes[link->vertex2][link->vertex1] = 1;
		free(link);
		ft_lstdelone(&farm->link_list, NULL);
		farm->link_list = temp;
	}
}

void		convert_read_data(t_antfarm *farm)
{
	t_link	*link;
	size_t	i;
	t_list	*temp;

	if (!farm->read_rooms_list->content ||
		!farm->read_rooms_list->next->content)
		invalid_farm();
	if (!(farm->room_arr = (t_room**)malloc(sizeof(t_room*) *
							farm->num_of_rooms)))
		mall_error();
	i = 0;
	while (farm->read_rooms_list)
	{
		farm->room_arr[i++] = *(t_room**)farm->read_rooms_list->content;
		temp = farm->read_rooms_list->next;
		ft_lstdelone(&farm->read_rooms_list, NULL);
		farm->read_rooms_list = temp;
	}
	farm->init_rooms->size = farm->num_of_rooms;
	if (!(farm->init_rooms->vertexes = (_Bool**)malloc(sizeof(_Bool*) *
										farm->num_of_rooms)))
		mall_error();
	link = NULL;
	fuck_the_norm(farm, link);
	optimize_graph(farm);
}
