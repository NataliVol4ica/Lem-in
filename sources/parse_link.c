/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:30:16 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 19:30:16 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include <stdlib.h>

static int	find_link_index(t_antfarm *farm, char *name)
{
	t_list *temp;
	t_room *troom;

	temp = farm->read_rooms_list;
	while (temp)
	{
		if (!temp->content)
			return (-1);
		troom = *(t_room**)temp->content;
		if (ft_strcmp(troom->name, name) == 0)
			return (troom->index);
		temp = temp->next;
	}
	return (-1);
}

static int	parse_link2(t_antfarm *farm, t_link *link)
{
	int diff;

	if (link->vertex1 < 0 || link->vertex2 < 0 ||
		link->vertex1 == link->vertex2)
	{
		diff = link->vertex1 - link->vertex2;
		free(link);
		return (diff == 0 ? 1 : 0);
	}
	ft_lstpushback(&farm->link_list, ft_lstnew((void*)&link, sizeof(t_link*)));
	return (1);
}

int			parse_link(t_antfarm *farm, char *str)
{
	char	**split_link;
	size_t	size_of_split_arr;
	t_link	*link;
	int		ret;

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
	ret = parse_link2(farm, link);
	free_word_arr(split_link);
	return (1);
}
