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

	if (!(farm->width_level = (int*)malloc(sizeof(int) * farm->rooms->size)))
		mall_error();
	i = -1;
	while (++i < farm->rooms->size)
		is_used[i] = 0;
	is_used[1] = 1;
	farm->width_level[1] = windex;
	farm->max_ant_per_step = farm->rooms->size;
	farm->len_of_shortest_path = -1;
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
		if (min < farm->max_ant_per_step && farm->len_of_shortest_path < 0)
			farm->max_ant_per_step = min;
		windex++;
	}
	farm->max_width = windex;
	farm->width_level[0] = windex;
}

void	fill_loadness(t_antfarm *farm, _Bool *busy_vertexes)
{
	size_t	curwidth;
	size_t	i;
	size_t	j;
	
	farm->loadness[0] = 1;
	curwidth = farm->max_width - 1;
	while (curwidth > 0)
	{
		//ft_printf("curwidth %d\n", curwidth);
		i = -1;
		while (++i < farm->num_of_rooms)
		{
			//ft_printf("%d width level %d isbusy %d\n", i, farm->width_level[i], busy_vertexes[i]);
			if (farm->width_level[i] == curwidth && !busy_vertexes[i])
			{
				//ft_printf("counting loadness for %d\n", i);
				farm->loadness[i] = 0;
				j = -1;
				while(++j < farm->num_of_rooms)
					if (!busy_vertexes[j] && farm->width_level[j] == curwidth + 1 &&
											farm->rooms->vertexes[i][j])
						farm->loadness[i] += farm->loadness[j];  
			}
		}curwidth--;
	}
}

void	pave_da_wei(t_antfarm *farm, size_t step, size_t antsleft)
{
	size_t	i;

	i = -1;
	while (++i < farm->path->len)
	{
		farm->steps[step + i][farm->num_of_ants - antsleft] = farm->path->vertexes[i];
		farm->busy_vertexes[step + i][farm->path->vertexes[i]] = 1;
	}
}

void	print_busy(t_antfarm *farm)
{
	size_t		i;
	size_t		j;

	i = -1;
	while (++i < farm->len_of_shortest_path + farm->num_of_ants && (j = -1))
	{
		while (++j < farm->num_of_rooms)
			ft_printf(" %d", farm->busy_vertexes[i][j]);
		ft_printf("\n");
	}
}

int		find_da_wei(t_antfarm *farm, size_t curstep, size_t antsleft, _Bool search_optimal)
{
	static int	sleep = 0;
	size_t		i;
	size_t		j;
	size_t		minwidthlevel;
	size_t		index;
	size_t		ret;
	size_t		curwidth;
	int			min_load;
	int			diff;

	if (sleep > 0)
	{
		sleep--;
		return (0);
	}
	//ft_printf("looking for step %d ants left %d optimal %d\n", curstep, antsleft, search_optimal);
	//print_busy(farm);
	//ft_printf(" LOOK AT THIS! %d\n", farm->len_of_shortest_path + farm->num_of_ants);
	/*i = -1;
	while (++i < farm->len_of_shortest_path + farm->num_of_ants && (j = -1))
	{
		while (++j < farm->num_of_ants)
		{ft_printf(" %d", farm->busy_vertexes[i][j]);
		}
		ft_printf("\n");
	}*/
	fill_loadness(farm, farm->busy_vertexes[curstep]);
	minwidthlevel = farm->max_width;
	//find a connected to start vertex
	//that is not busy
	//and has lowest width level. if equal - lowest loadness
	i = -1;
	while (++i < farm->rooms->size)
		if (farm->rooms->vertexes[0][i] && !farm->busy_vertexes[curstep][i])
			if (minwidthlevel > farm->width_level[i] ||
				(minwidthlevel == farm->width_level[i] && farm->loadness[index] > farm->loadness[index]))
			{
				minwidthlevel = farm->width_level[i];
				index = i;
			}
	//ft_printf("best neighbour vertex is %d of width level %d and loadness %d\n, index, minwidthlevel, farm->loadness[index]);
	if (!search_optimal) //for recursion check return len only
		return (minwidthlevel + 1);
	//if diff (this + 1) with shortest is > num of ants and search_optimal
	//for i from 1 to diff call find the way with curstep + i if step is less than steps len
	//cmp thisw + 1 with return.
	//if found path it better then sleep = i - 1 and return 0
	i = 1;
	diff = (int)minwidthlevel - (int)farm->len_of_shortest_path;
	//ft_printf("diff %d\n", diff);
	if (diff > (int)antsleft && search_optimal)
		while (i < minwidthlevel + 1 - farm->len_of_shortest_path - antsleft &&
			curstep + i + 1 < farm->len_of_shortest_path + farm->num_of_ants)
		{
			ret = find_da_wei(farm, curstep + i, antsleft, 0);
			if (minwidthlevel - ret - i > antsleft)
			{
				sleep = i - 1;
				return (0);
			}
			i++;
		}
	//find her neighbours of width_level - 1 with min loadness and add to the way
	//and push it all back to path
	// ... until width level is 0
	//return way len
	farm->path->len = 0;
	curwidth = minwidthlevel;
	farm->path->vertexes[farm->path->len++] = index;
	while (curwidth > 0)
	{
		min_load = -1;
		i = -1;
		while (++i < farm->num_of_rooms)
			if (farm->rooms->vertexes[farm->path->vertexes[farm->path->len - 1]][i] &&
				!farm->busy_vertexes[curstep + farm->path->len][i] &&
				farm->width_level[i] == curwidth - 1) //if next level of width is not busy and has connection
			{//if not in a bad mood
			//this should be fixed for loadness for proper level but not current
				if (min_load < 0 || min_load > farm->loadness[i])
				{
					min_load = farm->loadness[i];
					index = i;
				}
			}
		farm->path->vertexes[farm->path->len++] = index;
		curwidth--;
	}
	farm->path->vertexes[farm->path->len++] = 0;
	return (farm->path->len);
}

void	algo(t_antfarm *farm)
{
	size_t	curstep;
	size_t	antsleft;
	size_t	i;

	algo_mallocs(farm);
	algo_mallocs2(farm);
	curstep = 0;
	antsleft = farm->num_of_ants;
	while (antsleft > 0)
	{
		i = -1;
		while (++i < farm->max_ant_per_step)
			if (!find_da_wei(farm, curstep, antsleft, 1))
			{
				//ft_printf("der is no wae :'(\n");
				break;
			}
			else
			{
				pave_da_wei(farm, curstep, antsleft);
				antsleft--;
			}
		curstep++;
	}
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
	algo(farm);
	//print algo result
	//system("leaks lem-in");
	return (0);
}
