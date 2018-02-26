/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:30:59 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 19:30:59 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

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
