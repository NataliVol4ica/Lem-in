/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:30:21 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 19:30:21 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

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
	if (size_of_split_arr == 3 && !parse_room(farm, split_arr))
	{
		free_word_arr(split_arr);
		return (0);
	}
	else if (size_of_split_arr == 1 && !parse_link(farm, split_arr[0]))
	{
		free_word_arr(split_arr);
		return (0);
	}
	else if (size_of_split_arr != 3 && size_of_split_arr != 1)
		return (0);
	free_word_arr(split_arr);
	return (1);
}
