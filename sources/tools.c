/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:20:45 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 16:20:45 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"
#include "libft.h"

t_antfarm	*init_farm(void)
{
	t_antfarm	*farm;

	if (!(farm = (t_antfarm*)malloc(sizeof(t_antfarm))))
		mall_error();	
	farm->read_rooms_list = NULL;
	farm->link_list = NULL;
	farm->is_next_start = 0;
	farm->is_next_finish = 0;
	farm->finished_room_reading = 0;
	farm->read_rooms_list = NULL;
	ft_lstpushback(&farm->read_rooms_list, ft_lstnew((void*)0, 0));
	ft_lstpushback(&farm->read_rooms_list, ft_lstnew((void*)0, 0));
	farm->num_of_rooms = 2;
	return (farm);
}

void		free_room(t_room *room)
{
	free(room->name);
	free(room);
}