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

typedef struct	s_antfarn
{
	size_t	num_of_ants;

	size_t	num_of_rooms;
	t_graph	*rooms;

	t_list	*read_rooms_list;
	t_list	*link_to_next_room;
	t_graph	*init_rooms;
	_Bool	is_next_start;
	_Bool	is_next_finish;
	_Bool	finished_room_reading;
}				t_antfarm;

#endif
