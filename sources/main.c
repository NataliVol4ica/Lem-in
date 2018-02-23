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

int		parse_line(char *line, t_ant_farm *farm)
{
	t_room	*new_room;
	char	**split_arr;
	size_t	i;
	char	*str;
	char	*str2;

	if (line[0] == '#' || line[0] == 'L')
	{
		if (ft_strcmp(line, "##start") == 0)
		{
			if (farm->read_rooms_list->data)
				return (0);
			farm->is_next_start = true;
		}
		if (ft_strcmp(line, "##end") == 0)
		{
			if (farm->read_rooms_list->next->data)
				return (0);
			farm->is_next_finish = true;
		}
		return (1);
	}
	split_arr = ft_strsplit(line);
	free(line);
	i = 0;
	while (split_arr[i])
		i++;
	
	if (i == 3) // room
	{
		if (farm->finished_room_reading) //esli komnata posle linkov
			return (0);
		//parse room
	}
	else if (i == 1) //link
	{
		farm->finished_room_reading = 1;
		//parse link
	}
	else
		return (0);
	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		malloc_error();
	return (1);
}

int		main(int ac, char **av)
{
	char		*line;
	t_list		*readlist;
	t_ant_farm	*farm;

	if (ac != 1)
		argnum_error();
	if (!(farm = (t_ant_farm*)malloc(sizeof(t_ant_farm))))
		malloc_error();
	farm->num_of_ants = -1;
	farm->is_next_start = 0;
	farm->is_next_finish = 0;
	farm->finished_room_reading = 0;
	farm->read_rooms_list = NULL;
	ft_lstpushback(farm->read_rooms_list, ft_lstnew((void*)0, 0));
	ft_lstpushback(farm->read_rooms_list, ft_lstnew((void*)0, 0));
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
