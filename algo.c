/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:10:06 by snunes            #+#    #+#             */
/*   Updated: 2019/06/02 15:18:08 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_map(char **map)
{
	int y;
	int len;

	len = ft_strlen(map[0]);
	y = 0;
	while (y < len)
	{
		write(1, map[y], len);
		write(1, "\n", 1);
		y++;
	}
}

int		ft_dot(char **map, int mode, int x, int y)
{
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '1' && mode == 4)
				map[y][x] = '.';
			else if (map[y][x] == '.' && mode == 1)
				return (y * 20 + x);
			++x;
		}
		x = 0;
		++y;
	}
	return (-2);
}

int		ft_putpiece(char **map, char tab[5][5], int retx, int rety)
{
	int y;
	int x;

	y = 0;
	x = -1;
	while (tab[0][++x] == '.')
		--retx;
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

int		find_space(char **map, t_piece *tet, int **pos)
{
	int i;
	int x;
	int y;

	x = pos[tet->nb][1];
	y = pos[tet->nb][2];
	if ((i = ft_dot(map, 1, x, y)) == -2)
		return (i);
	x = i % 20;
	y = (i - x) / 20;
	i = ft_putpiece(map, tet->tab, x, y);
	pos[tet->nb][1] = (map[y][x + 1] == '\0') ? 0 : x + 1;
	pos[tet->nb][2] = (pos[tet->nb][1] == 0) ? y + 1 : y;
	if (i == EXIT_FAILURE)
	{
		ft_dot(map, 4, x, y);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
