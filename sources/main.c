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

int		parse_comment(char *line, t_antfarm *farm)
{
	if (farm->is_next_start || farm->is_next_finish)
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

int		parse_line(char *line, t_antfarm *farm)
{
	char	**split_arr;
	char	**split_link;
	size_t	size_of_split_arr;
	char	*str;
	char	*str2;

	if (line[0] == '#' || line[0] == 'L')
		return (parse_comment(line, farm));
	split_arr = ft_split_whitespaces(line);
	size_of_split_arr = 0;
	while (split_arr[size_of_split_arr])
		size_of_split_arr++;
	if (size_of_split_arr == 3) // room
	{
		if (!parse_room(farm, split_arr))
			return (0);
	}
	else if (size_of_split_arr == 1) //link
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
	farm->num_of_rooms = 2;
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
		if (!parse_line(line, farm))
		{
			free(line);
			break;
		}
		ft_lstpushback(&readlist, ft_lstnew((void*)line, ft_strlen(line)));
		free(line);
	}
	//convert read data to struct final mid-form
	//check if the data is enough
	//print the read farm list
	//free read farm list
	//run algo
	//print algo result
	return (0);
}
