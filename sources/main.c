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

void	print_read_list(t_list *readlist)
{
	t_list	*temp;

	temp = readlist;
	while (readlist)
	{
		ft_printf("%s\n", *(char**)readlist->content);
		free(*(char**)readlist->content);
		readlist = readlist->next;
	}
	ft_lstdel(&temp, NULL);
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
	readlist = NULL;
	while ((get_next_line(0, &line) > 0))
	{
		if (!parse_line(line, farm))
		{
			free(line);
			break;
		}
		ft_lstpushback(&readlist, ft_lstnew((void*)&line, sizeof(char*)));
	}
	//convert read data to struct final mid-form
	//check if the data is enough
	//free lists data properly!
	print_read_list(readlist);	
	//run algo
	//print algo result
	system("leaks lem-in");
	return (0);
}
