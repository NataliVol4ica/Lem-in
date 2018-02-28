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

void	depth_search(t_antfarm *farm)
{
	size_t	prev_vertex;
	size_t	i;
	size_t	j;

	prev_vertex = farm->depth_search_arr[farm->depth_level - 1];
	i = -1;
	while (++i < farm->num_of_rooms)
	{
		if (i == prev_vertex || farm->is_vertex_visited[i] || farm->is_depth_chain_vertex[i])
			continue;
		if (farm->init_rooms->vertexes[prev_vertex][i])
		{
			farm->depth_search_arr[farm->depth_level++] = i;
			if (i == 1)
			{
				j = -1;
				while (++j < farm->depth_level)
					farm->is_new_graph_vertex[farm->depth_search_arr[j]] = 1;
				farm->is_vertex_visited[0] = 1;
				farm->depth_level--;
				return;
			}
			depth_search(farm);
			farm->depth_level--;
		}
	}
	farm->is_vertex_visited[prev_vertex] = 1;
}

void	cut_graph(t_antfarm *farm)
{
	size_t i;

	if (!(farm->is_new_graph_vertex = (_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
		mall_error();

	if (!(farm->is_depth_chain_vertex = (_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->is_vertex_visited = (_Bool*)malloc(sizeof(_Bool) * farm->num_of_rooms)))
		mall_error();
	if (!(farm->depth_search_arr = (int*)malloc(sizeof(int) * farm->num_of_rooms)))
		mall_error();
	i = -1;
	while (++i < farm->num_of_rooms)
	{
		farm->is_new_graph_vertex[i] = 0;
		farm->is_depth_chain_vertex[i] = 0;
		farm->is_vertex_visited[i] = 0;
	}
	farm->is_depth_chain_vertex[0] = 1;
	farm->depth_level = 1;
	farm->depth_search_arr[0] = 0;
	depth_search(farm);
	//free depth search list ?
	
	//check num of new vertexes. if zero print error
	//get a data of ok vertexes
	//create an arr that converts each new vertex index to an old one
	//create new graph
	//free old graph
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
	cut_graph(farm);
	print_read_list(readlist);	
	//run algo
	//print algo result
	//system("leaks lem-in");
	return (0);
}
