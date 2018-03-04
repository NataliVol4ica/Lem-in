/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:27:34 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:27:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void	mall_error(void)
{
	ft_printf("Error: Malloc fail!\n");
	exit(1);
}

void	argnum_error(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		return ;
	ft_printf("Usage: ./lem-in\n");
	exit(0);
}

void	invalid_farm(void)
{
	ft_printf("ERROR\n");
	exit(1);
}
