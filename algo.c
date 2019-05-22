/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:10:06 by snunes            #+#    #+#             */
/*   Updated: 2019/05/22 22:26:01 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_dot(char **map, int mode)
{
	int i;
	int j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' && mode == 2)
				map[j][i] = '.';
			else if (map[j][i] == '1' && mode == 4)
				map[j][i] = '.';
			else if (map[j][i] == '.' && mode == 1)
					return (j * 20 + i);
			else if (map[j][i] == '.' && mode == 3)
			{
				map[j][i] = '0';
				return (EXIT_SUCCESS);
			}
			++i;
		}
		++j;
	}
	return (-2);
}

int		ft_putpiece(char **map, char tab[5][5], int retx, int rety)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (tab[0][x] == '.')
	{
		++x;
		--retx;
	}
	if (retx < 0)
		return (EXIT_FAILURE);
	while (y != 4)
	{
		x = 0;
		while (x != 4)
		{
			if (tab[y][x] == '#' && map[rety + y]
					&& map[rety + y][retx + x] == '.')
				map[rety + y][retx + x] = '1';
			else if (tab[y][x] == '#')
				return (EXIT_FAILURE);
			++x;
		}
		++y;
	}
	return (EXIT_SUCCESS);
}

int		find_space(char **map, t_piece *piece)
{
	int i;
	int x;
	int y;

	if ((i = ft_dot(map, 1)) == -2)
		return (-2);
	x = i % 20;
	y = (i - x) / 20;
	if (ft_putpiece(map, piece->tab,  x, y) == EXIT_FAILURE)
	{
		ft_dot(map, 4);
		ft_dot(map, 3);
		return (EXIT_FAILURE);
	}
	ft_dot(map, 2);
	return (EXIT_SUCCESS);
}
