/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:56:13 by snunes            #+#    #+#             */
/*   Updated: 2019/05/18 23:20:15 by snunes           ###   ########.fr       */
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
			else if (map[j][i] == '.')
			{
				if (mode == 1)
					return (j * 20 + i);
				else if (mode == 3)
					map[j][i] = '0';
			}
			++i;
		}
		++j;
	}
	return (EXIT_FAILURE);
}



int		size_piece(char tab[5][5])
{
	int x;
	int y;
	int way;

	y = 0;
	printf("prochaine piece a placer :\n");
	while (y < 4)
	{
		printf("%s\n", tab[y]);
		y++;
	}
	x = 3;
	y = 3;
	way = 1;
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

int		ft_putpiece(char **map, int size, int x, int y)
{
	int jump;

	jump = 0;
	while (size > 5)
	{
		jump++;
		if (size % 17 == 0)
		{
			if (map[y][x] != '.')
				return (EXIT_FAILURE);
			map[y][x] = '#';
			x++;
			size = size / 17;
		}
		else
		{
			x++;
			size -= 2;
		}
		if (jump % 4 == 0)
		{
			y++;
			x = 0;
		}
	}
	return (EXIT_SUCCESS);
}

int		find_space(char **map, t_piece *piece, int try)
{
	int i;
	int x;
	int y;
	int size;

	i = 0;
	while (i < try)
	{
		if (ft_dot(map, 3) == EXIT_FAILURE)
			return (-2);
		i++;
	}
	i = ft_dot(map, 1);
	x = i % 20;
	y = (i - x) / 20;
	size = size_piece(piece->tab);
	if (ft_putpiece(map, size, x, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_dot(map, 2);
	return (EXIT_SUCCESS);
}
