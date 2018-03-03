/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:18 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:18 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <string.h>
# include "libft_structures.h"

typedef struct	s_room
{
	char	*name;
	int		x_coord;
	int		y_coord;
	int		index;
}				t_room;

typedef struct	s_link
{
	int		vertex1;
	int		vertex2;
}				t_link;

typedef struct	s_graph
{
	_Bool	**vertexes;
	size_t	size;
}				t_graph;

typedef struct	s_path
{
	int		*vertexes;
	int		len;
}				t_path;

typedef struct	s_antfarn
{
	size_t	num_of_ants;
	size_t	num_of_rooms;
	t_room	**room_arr;
	t_graph	*rooms;
	int		*width_level;
	int		*loadness;
	size_t	max_width;
	size_t	len_of_shortest_path;
	size_t	max_ant_per_step;
	int		**steps;
	_Bool	**busy_vertexes;

	t_path	*path;

	int		*old_to_new;
	int		*new_to_old;

	_Bool	*is_wd_chain_vertex;
	_Bool	*is_vertex_visited;
	int		*wd_search_arr;
	int		depth_level;

	t_graph	*init_rooms;
	_Bool	*is_new_graph_vertex;
	t_list	*read_rooms_list;
	t_list	*link_list;
	_Bool	is_next_start;
	_Bool	is_next_finish;
	_Bool	finished_room_reading;
}				t_antfarm;

#endif
