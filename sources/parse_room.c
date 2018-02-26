/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:19:24 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 16:19:25 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include <stdlib.h>

_Bool	is_room_unique(t_antfarm *farm, t_room *room)
{
	t_list *temp;
	t_room *troom;

	temp = farm->read_rooms_list;
	if (ft_strchr(room->name, '-'))
		return (0);
	while (temp)
	{
		if (!temp->content)
		{
			temp = temp->next;
			continue ;
		}
		troom = (t_room*)temp->content;
		if (strcmp(troom->name, room->name) == 0)
			return (0);
		if (room->x_coord == troom->x_coord && room->y_coord == troom->y_coord)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	add_start_room(t_antfarm *farm, t_room *new_room)
{
	t_list	*newl;

	farm->is_next_start = 0;
	new_room->index = 0;
	if (!(newl = ft_lstnew((void*)new_room, sizeof(t_list))))
		mall_error();
	newl->next = farm->read_rooms_list->next;
	ft_lstdelone(&farm->read_rooms_list, NULL);
	farm->read_rooms_list = newl;
}

void	add_finish_room(t_antfarm *farm, t_room *new_room)
{
	t_list	*newl;

	farm->is_next_finish = 0;
	new_room->index = 1;
	if (!(newl = ft_lstnew((void*)new_room, sizeof(t_list))))
		mall_error();
	newl->next = farm->read_rooms_list->next->next;
	ft_lstdelone(&farm->read_rooms_list->next, NULL);
	farm->read_rooms_list->next = newl;
}

void	add_casual_room(t_antfarm *farm, t_room *new_room)
{
	t_list	*newl;

	new_room->index = farm->num_of_rooms++;
	if (!(newl = ft_lstnew((void*)new_room, sizeof(t_list))))
		mall_error();
	ft_lstpushback(&farm->read_rooms_list, newl);
}

int		parse_room(t_antfarm *farm, char **split_arr)
{
	t_room	*new_room;

	if (farm->finished_room_reading)
		return (0);
	if (!is_integer(split_arr[1]) || !is_integer(split_arr[2]))
		return (0);
	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		mall_error();
	new_room->name = ft_strdup(split_arr[0]);
	new_room->x_coord = ft_atoi(split_arr[1]);
	new_room->y_coord = ft_atoi(split_arr[2]);
	if (!is_room_unique(farm, new_room))
	{
		free_word_arr(split_arr);
		free_room(new_room);
		return (0);
	}
	if (farm->is_next_start)
		add_start_room(farm, new_room);
	else if (farm->is_next_finish)
		add_finish_room(farm, new_room);
	else
		add_casual_room(farm, new_room);
	return (1);
}
