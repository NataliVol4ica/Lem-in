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
	if (!(farm->init_rooms = (t_graph*)malloc(sizeof(t_graph))))
		mall_error();
	if (!(farm->rooms = (t_graph*)malloc(sizeof(t_graph))))
		mall_error();
	return (farm);
}

void		free_room(t_room *room)
{
	free(room->name);
	free(room);
}

void		print_read_list(t_list *readlist)
{
	t_list	*temp;

	temp = readlist;
	while (readlist)
	{
		ft_printf("%s\n", *(char**)readlist->content);
		free(*(char**)readlist->content);
		readlist = readlist->next;
	}
	ft_printf("\n");
	ft_lstdel(&temp, NULL);
}

int			max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
