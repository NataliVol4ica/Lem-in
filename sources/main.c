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

void	skip_ws(char *line, size_t *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		*i = *i + 1;
}

void	free_room(t_room *room)
{
	free(room->name);
	free(room);
}

_Bool	is_room_unique(t_antfarm *farm, t_room *room)
{
	t_list *temp;
	t_room *troom;

	temp = farm->read_rooms_list;
	while (temp)
	{
		if (!temp->content)
			continue ;
		troom = (t_room*)temp->content;
		if (strcmp(troom->name, room->name) == 0)
			return (0);
		if (room->x_coord == troom->x_coord && room->y_coord == troom->y_coord)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int		parse_line(char *line, t_antfarm *farm)
{
	t_room	*new_room;
	char	**split_arr;
	size_t	i;
	char	*str;
	char	*str2;
	t_list	*newl;

	if (line[0] == '#' || line[0] == 'L')
	{
		if (farm->is_next_start || farm->is_next_finish) //esli ojidalas room
			return (0);
		if (ft_strcmp(line, "##start") == 0)
		{
			if (farm->read_rooms_list->content)
				return (0);
			farm->is_next_start = 1;
		}
		if (ft_strcmp(line, "##end") == 0)
		{
			if (farm->read_rooms_list->next->content)
				return (0);
			farm->is_next_finish = 1;
		}
		return (1);
	}
	split_arr = ft_split_whitespaces(line);
	free(line);
	i = 0;
	while (split_arr[i])
		i++;
	
	if (i == 3) // room
	{
		if (farm->finished_room_reading) //esli komnata posle linkov
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
		newl = ft_lstnew((void*)new_room, sizeof(new_room));
		if (farm->is_next_start)
		{
			farm->is_next_start = 0;
			newl->next = farm->read_rooms_list->next;
			ft_lstdelone(&farm->read_rooms_list, NULL);
			farm->read_rooms_list = newl;
		}
		else if (farm->is_next_finish)
		{
			farm->is_next_finish = 0;
			newl->next = farm->read_rooms_list->next->next;
			ft_lstdelone(&farm->read_rooms_list->next, NULL);
			farm->read_rooms_list->next = newl;
		}
		else
			ft_lstpushback(&farm->read_rooms_list, newl);
		farm->num_of_rooms++;
	}
	else if (i == 1) //link
	{
		farm->finished_room_reading = 1;
		//parse link
		//if names are equal
		//continue;
		//search names of the rooms
		//if no names found
		//break;
		//otherwise add link to list
	}
	else
		return (0);
	free_word_arr(split_arr);
	return (1);
}

t_antfarm	*init_farm(void)
{
	t_antfarm	*farm;

	if (!(farm = (t_antfarm*)malloc(sizeof(t_antfarm))))
		mall_error();	
	farm->num_of_ants = -1;
	farm->is_next_start = 0;
	farm->is_next_finish = 0;
	farm->finished_room_reading = 0;
	farm->read_rooms_list = NULL;
	ft_lstpushback(&farm->read_rooms_list, ft_lstnew((void*)0, 0));
	ft_lstpushback(&farm->read_rooms_list, ft_lstnew((void*)0, 0));
	return (farm);
}

int		main(int ac, char **av)
{
	char		*line;
	t_list		*readlist;
	t_antfarm	*farm;

	if (ac != 1)
		argnum_error();
	farm = init_farm();
	readlist = NULL;
	while ((get_next_line(0, &line) > 0))
	{
		ft_lstpushback(&readlist, ft_lstnew((void*)line, ft_strlen(line)));
		if (!parse_line(line, farm))
			break;
	}
	//convert read data to struct final mid-form
	//check if the data is enough
	//print the read farm list
	//free read farm list
	//run algo
	//print algo result
	return (0);
}
