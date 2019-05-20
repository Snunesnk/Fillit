/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:56:13 by snunes            #+#    #+#             */
/*   Updated: 2019/05/20 23:34:21 by snunes           ###   ########.fr       */
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
			else if (map[j][i] == '.')
			{
				if (mode == 1)
					return (j * 20 + i);
				else if (mode == 3)
				{
					map[j][i] = '0';
//					printf("et une place mise a '0' en [%d, %d]\n", i, j);
					return (EXIT_SUCCESS);
				}
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

	y = 0;
/*	printf("\nprochaine piece a placer :\n");
	while (y < 4)
	{
		printf("%s\n", tab[y]);
		y++;
	}*/
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

int		ft_putpiece(char **map, int size, int x, int y)
{
	int ret;
	int dot;

	dot = 0;
	ret = x;
//	printf("coordonees de depart : [%d, %d]\n", x, y);
	while ((size - dot) % 17 != 0)
	{
		dot += 2;
		--ret;
	}
	x = ret;
	if (ret < 0)
		return (EXIT_FAILURE);
	while (size > 34 && map[y])
	{
//		printf("on se situe en [%d, %d]\n", x, y);
		if (size % 17 == 0)
		{
			if ((size_t)x > ft_strlen(map[0]) || map[y][x] != '.')
				return (EXIT_FAILURE);
//			printf("On place un bloc en ici !\n");
			map[y][x] = '1';
			size = size / 17;
		}
		else
			size -= 2;
		++x;
		if (x - ret == 4)
		{
			++y;
			x = ret;
		}
	}
	if (!map[y])
		return (EXIT_FAILURE);
//	printf("tout les blocs sont places\n");
	return (EXIT_SUCCESS);
}

int		find_space(char **map, t_piece *piece)
{
	int i;
	int x;
	int y;
	int size;

	if ((i = ft_dot(map, 1)) == -2)
	{
//		printf("et c'est un rate du ft dot\n");
		return (-2);
	}
	x = i % 20;
	y = (i - x) / 20;
/*	printf("\non va placer la prochaine piece dans :\n");
	print_map(map);*/
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
