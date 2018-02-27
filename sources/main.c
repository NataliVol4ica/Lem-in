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

void	print_read_list(t_list *readlist)
{
	t_list	*temp;

	temp = readlist;
	while (readlist)
	{
		ft_printf("%s\n", *(char**)readlist->content);
		free(*(char**)readlist->content);
		readlist = readlist->next;
	}
	ft_lstdel(&temp, NULL);
}

void	convert_read_data(t_antfarm *farm)
{
	t_list	*temp;
	t_link	*link;
	size_t	i;
	size_t	j;

	if (!farm->read_rooms_list->content || !farm->read_rooms_list->next->content)
		invalid_farm();
	if (!(farm->rooms = (t_room**)malloc(sizeof(t_room*) * farm->num_of_rooms)))
		mall_error();
	i = 0;
	while (farm->read_rooms_list)
	{
		farm->rooms[i++] = *(t_room**)farm->read_rooms_list->content;
		temp = farm->read_rooms_list->next;
		ft_lstdelone(&farm->read_rooms_list, NULL);
		farm->read_rooms_list = temp;
	}
	if (!(farm->init_rooms = (t_graph*)malloc(sizeof(t_graph))))
		mall_error();
	farm->init_rooms->size = farm->num_of_rooms;
	if (!(farm->init_rooms->vertexes = (_Bool**)malloc(sizeof(_Bool*) * farm->num_of_rooms)))
		mall_error();
	i = -1;
	while (++i < farm->num_of_rooms)
	{
		if (!(farm->init_rooms->vertexes[i] = (_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
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
	free(line);
	readlist = NULL;
	while ((get_next_line(0, &line) > 0))
	{
		if (!parse_line(line, farm))
		{
			free(line);
			break;
		}
		ft_lstpushback(&readlist, ft_lstnew((void*)&line, sizeof(char*)));
	}
	convert_read_data(farm);
	//check if the data is enough - if there is a path between s and f
	print_read_list(readlist);	
	//run algo
	//print algo result
	system("leaks lem-in");
	return (0);
}
