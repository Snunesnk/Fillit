/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:49:53 by snunes            #+#    #+#             */
/*   Updated: 2019/05/25 20:23:29 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**size_square(int side)
{
	int		i;
	int		j;
	char	**square;

	i = 0;
	if (!(square = (char **)ft_memalloc(sizeof(*square) * (side + 1))))
		return (NULL);
	while (i < side)
	{
		j = 0;
		if (!(square[i] = (char *)ft_memalloc(sizeof(char) * (side + 1))))
		{
			while (--i)
				free(square[i]);
			free(square);
		}
		while (j < side)
		{
			square[i][j] = '.';
			++j;
		}
		++i;
	}
	square[i] = NULL;
	return (square);
}

void	order_map(char **map, t_list *lst, int length, int mode)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (map[y])
	{
		if (map[y][x] == '1' && mode == 1)
			map[y][x] = 'A' + length - ft_lst_length(lst);
		else if (map[y][x] == 'A' + length - ft_lst_length(lst) && mode == 2)
			map[y][x] = '.';
		++x;
		if (!map[y][x])
		{
			x = 0;
			++y;
		}
	}
}

void	clear(int **coord, int i, int length)
{
	int		j;
	int		ret;

	ret = i;
	j = 0;
	while (j < length)
	{
		if (coord[i + j][0] == i + j)
		{
			coord[i + j][1] = 0;
			coord[i + j][2] = 0;
		}
		else
		{
			ret = i - 1 + j;
			while (coord[ret][0] != coord[i + j][0])
				--ret;
			coord[i + j][1] = coord[ret][1];
			coord[i + j][2] = coord[ret][2];
		}
		++j;
	}
}

int		recursive(t_list *lst, char **map, int **coord, int length)
{
	int res;

	if (!lst)
		return (EXIT_SUCCESS);
	clear(coord, ((t_piece *)(lst->content))->nb, 1);
	while ((res = find_space(map, ((t_piece *)(lst->content)), coord)) != -2)
	{
		if (res == EXIT_SUCCESS)
		{
			order_map(map, lst, length, 1);
			if (recursive(lst->next, map, coord, length) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
		}
	}
	order_map(map, lst, length - 1, 2);
	return (EXIT_FAILURE);
}

int		ft_fillit(t_list *lst, int **coord)
{
	char	**map;
	int		i;
	int		length;

	length = ft_lst_length(lst);
	i = ft_sqrt(length * 4);
	if (!(map = size_square(i)))
		return (EXIT_FAILURE);
	while (recursive(lst, map, coord, length) != EXIT_SUCCESS)
	{
		clear(coord, 1, length);
		++i;
		free_map(map);
		if (!(map = size_square(i)))
			return (EXIT_FAILURE);
	}
	print_map(map);
	free_map(map);
	return (EXIT_SUCCESS);
}
