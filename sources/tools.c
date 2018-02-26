/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:20:45 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 16:20:45 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"

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
