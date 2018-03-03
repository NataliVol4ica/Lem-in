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

void		convert_read_data(t_antfarm *farm);
void		optimize_graph(t_antfarm *farm);

/*
** INPUT VALIDATION
*/

int			parse_line(char *line, t_antfarm *farm);
int			parse_comment(char *line, t_antfarm *farm);
int			parse_room(t_antfarm *farm, char **split_arr);
int			parse_link(t_antfarm *farm, char *str);

/*
** TOOLS
*/

t_antfarm	*init_farm(void);
void		free_room(t_room *room);
void		print_read_list(t_list *readlist);

/*
** MALLOCS
*/

void		optimization_mallocs(t_antfarm *farm);
void		new_graph_mallocs(t_antfarm *farm);
void		algo_mallocs(t_antfarm *farm);
void		algo_mallocs2(t_antfarm *farm);
/*
** ERRORS
*/

void		argnum_error(void);
void		mall_error(void);
void		invalid_farm(void);

#endif
