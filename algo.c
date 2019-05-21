/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:56:13 by snunes            #+#    #+#             */
/*   Updated: 2019/05/21 18:29:55 by snunes           ###   ########.fr       */
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

int		size_piece(char tab[5][5])
{
	int x;
	int y;
	int way;

	x = 3;
	y = 3;
	way = 2;
	while (y >= 0)
	{
		if (tab[y][x] == '#')
			way *= 17;
		else
			way += 2;
		x--;
		if (x < 0)
		{
			x = 3;
			--y;
		}	
	}
	return (way);
}

int		test_place(char *line, int *size, int retx, int len)
{
	int x;

	x = 0;
	while (x != 4 && *size >= 34)
	{
		if (*size % 17 == 0)
		{
			if (line[retx + x] != '.' || retx + x >= len)
				return (EXIT_FAILURE);
			line[retx + x] = '1';
			*size = *size / 17;
		}
		else
			*size -= 2;
		++x;
	}
	return (EXIT_SUCCESS);
}

int		ft_putpiece(char **map, int size, int retx, int rety)
{
	int dot;
	int y;
	int len;

	len = ft_strlen(map[0]);
	y = 0;
	dot = 0;
	while ((size - dot) % 17 != 0)
	{
		dot += 2;
		--retx;
	}
	while (y < 4 && map[rety + y] && retx >= 0)
	{
		if (test_place(map[rety + y], &size, retx, len) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (size < 34)
			return (EXIT_SUCCESS);
		y++;
	}
	return (EXIT_FAILURE);
}

int		find_space(char **map, t_piece *piece)
{
	int i;
	int x;
	int y;
	int size;

	if ((i = ft_dot(map, 1)) == -2)
		return (-2);
	x = i % 20;
	y = (i - x) / 20;
	size = size_piece(piece->tab);
	if (ft_putpiece(map, size, x, y) == EXIT_FAILURE)
	{
		ft_dot(map, 4);
		ft_dot(map, 3);
		return (EXIT_FAILURE);
	}
	ft_dot(map, 2);
	return (EXIT_SUCCESS);
}
