/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:11 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:11 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "structures.h"

/*
** ROOM PARSING
*/

int		parse_room(t_antfarm *farm, char **split_arr);

/*
** TOOLS
*/


void	skip_ws(char *line, size_t *i);
void	free_room(t_room *room);

/*
** ERRORS
*/

void	argnum_error(void);
void	mall_error(void);
void	invalid_farm(void);

#endif
