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

void	width_numeration(t_antfarm *farm)
{
	_Bool	is_used[farm->rooms->size];
	int		windex = 0;
	int		i;
	int		j;
	int		num_of_used;
	size_t	min;

	if (!(farm->widthnum = (int*)malloc(sizeof(int) * farm->rooms->size)))
		mall_error();
	i = -1;
	while (++i < farm->rooms->size)
		is_used[i] = 0;
	is_used[1] = 1;
	farm->width_level[1] = windex;
	farm->max_ant_per_step = farm->rooms->size;
	farm->len_of_shortest_path = farm->rooms->size;
	num_of_used = farm->rooms->size - 1;
	while (num_of_used)
	{
		min = 0;
		i = -1;
		while (++i < farm->rooms->size)
			if (is_used[i] && farm->width_level[i] == windex)
			{
				j = -1;
				while (++j < farm->rooms->size)
					if (!is_used[j] && farm->rooms->vertexes[i][j])
					{
						farm->width_level[j] = windex + 1;
						is_used[j] = 1;
						if (j == 0)
							farm->len_of_shortest_path = windex + 1;
						num_of_used--;
						min++;
					}
			}
		if (min < farm->max_ant_per_step)
			farm->max_ant_per_step = min;
		windex++;
	}
	farm->max_width = windex;
	farm->width_level[0] = windex;
}

void	fill_loadness(t_antfarm *farm, _Bool *busy_vertexes)
{
	//loadness[0] = 1
	//curwidth = max_width
	//while curwidth != 0
	//find all wertexes with width level curwidth
	//that are not busy
	//for every curlevel vertex
	//find a sum of loadness of every connected prevlevel vertex loadness
	//those vertexes should not be busy too
	//curwidth--
}

void	pave_da_wei(t_antfarm *farm, size_t step)
{
	//for i from 0 to path len - 1
	//farm->steps[step + i][antnum - antleft] = farm->path->vertexes[i]
	//farm->busy_vertexes[step + i][farm->path->vertexes[i] = 1;
}

int		find_da_wei(t_antfarm *farm, size_t curstep/*hz*/, _Bool search_optimal)
{
	static int sleep = 0;

	if (sleep > 0)
		{
			sleep--;
			return (0);
		}
	//fill loadness
	//find a connected to start vertex
	//that is not busy
	//and has lowest width level. if equal - lowest loadness
	//if diff (this + 1) with shortest is <= num of ants or !search_optimal
	//find her neighbours of width_level - 1 with min loadness and add to the way
	//and push it all back to path
	// ... until width level is 0
	//otherwise
	//for i from 1 to diff call find the way with curstep + i if step is less than steps len
	//cmp thisw + 1 with return.
	//if found path it better sleep = i - 1 and return 0
	//return way len
}

void	algo(t_antfarm *farm)
{
	//allocate array of loadness[numofrooms]
	//allocate arrays of steps and busy vertexes
	//height - shortest + ants - 1;
	//len = num of ants and fill them with -1 || false
	//curstep = 0
	//antsleft = num_of_ants;
	//while (antsleft > 0)
	//for i from 1 to max_ant_per_step
	//if not found way break
	//else pave found path
	//step++
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
			break ;
		}
		ft_lstpushback(&readlist, ft_lstnew((void*)&line, sizeof(char*)));
	}
	convert_read_data(farm);
	optimize_graph(farm);
	print_read_list(readlist);
	width_numeration(farm);
	//run algo
	//print algo result
	//system("leaks lem-in");
	return (0);
}
