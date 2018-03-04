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

void	print_ans(t_antfarm *farm)
{
	int		i;
	size_t	j;
	_Bool	is_first;
	_Bool	printed;

	i = -1;
	while (++i < farm->total_steps)
	{
		printed = 0;
		j = -1;
		is_first = 1;
		while (++j < farm->num_of_ants)
			if (farm->steps[i][j] > 0)
			{
				printed = 1;
				if (!is_first)
					ft_printf(" ");
				ft_printf("L%d-%s", j + 1,
					farm->room_arr[farm->new_to_old[farm->steps[i][j]]]->name);
				is_first = 0;
			}
		if (printed)
			ft_printf("\n");
	}
}

int		main(int ac, char **av)
{
	char		*line;
	t_list		*readlist;
	t_antfarm	*farm;

	argnum_error(ac, av);
	farm = init_farm();
	if (!(get_next_line(0, &line) > 0) || !is_integer(line) ||
		(farm->num_of_ants = ft_atoi(line)) <= 0)
		invalid_farm();
	readlist = NULL;
	ft_lstpushback(&readlist, ft_lstnew((void*)&line, sizeof(char*)));
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
	print_read_list(readlist);
	width_numeration(farm);
	algo(farm);
	return (0);
}
