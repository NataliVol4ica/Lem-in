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

int		find_link_index(t_antfarm *farm, char *name)
{
	t_list *temp;
	t_room *troom;

	temp = farm->read_rooms_list;
	while (temp)
	{
		if (!temp->content)
			return (-1);
		troom = (t_room*)temp->content;
		if (strcmp(troom->name, name) == 0)
			return (troom->index);
		temp = temp->next;
	}
	return (-1);
}

int		parse_link(t_antfarm *farm, char *str)
{
	char	**split_link;
	size_t	size_of_split_arr;
	t_link	*link;
	int 	diff;

	farm->finished_room_reading = 1;
	split_link = ft_strsplit(str, '-');
	size_of_split_arr = 0;
	while (split_link[size_of_split_arr])
		size_of_split_arr++;
	if (size_of_split_arr != 2)
	{
		free_word_arr(split_link);
		return (0);
	}
	if (!(link = (t_link*)malloc(sizeof(t_link))))
		mall_error();
	link->vertex1 = find_link_index(farm, split_link[0]);
	link->vertex2 = find_link_index(farm, split_link[1]);
	if (link->vertex1 < 0 || link->vertex2 < 0 || link->vertex1 == link->vertex2)
	{
		diff = link->vertex1 - link->vertex2;
		free(link);
		free_word_arr(split_link);
		return (diff == 0 ? 1 : 0);
	}
	ft_lstpushback(&farm->link_list, ft_lstnew((void*)link, sizeof(link)));
	return (1);
}

int		parse_line(char *line, t_antfarm *farm)
{
	char	**split_arr;
	size_t	size_of_split_arr;

	if (line[0] == '#' || line[0] == 'L')
		return (parse_comment(line, farm));
	split_arr = ft_split_whitespaces(line);
	size_of_split_arr = 0;
	while (split_arr[size_of_split_arr])
		size_of_split_arr++;
	if (size_of_split_arr == 3) // room
	{
		if (!parse_room(farm, split_arr))
		{
			free_word_arr(split_arr);
			return (0);
		}
	}
	else if (size_of_split_arr == 1) //link
	{
		if (!parse_link(farm, split_arr[0]))
		{
			free_word_arr(split_arr);
			return (0);
		}
	}
	else
		return (0);
	free_word_arr(split_arr);
	return (1);
}

int		main(int ac, char **av)
{
	char		*line;
	t_list		*readlist;
	t_antfarm	*farm;

	if (ac != 1)
		argnum_error();
	farm = init_farm();
	if (!(get_next_line(0, &line) > 0) || !is_integer(line) ||
		(farm->num_of_ants = ft_atoi(line)) <= 0)
		invalid_farm();
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
