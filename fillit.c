/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:49:53 by snunes            #+#    #+#             */
/*   Updated: 2019/05/21 18:39:56 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**size_square(int side)
{
	int	i;
	int j;
	char **square;

	i = 0;
	if(!(square = (char **)ft_memalloc(sizeof(*square) * side + 1)))
		return (NULL);
	while (i < side)
	{
		j = 0;
		if (!(square[i] = (char *)ft_memalloc(sizeof(char) * side + 1)))
		{
			while (i)
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
	int first;

	first = 0;
	y = 0;
	x = 0;
	while (map[y])
	{
		if (map[y][x] == '1' && mode == 1)
			map[y][x] = 'A' + length - ft_lst_length(lst);
		else if ((map[y][x] == '9' && mode == 3))
			map[y][x] = '.';
		else if (map[y][x] == '.' && mode == 2 && first == 0)
			map[y][x] = '9';
		else if (map[y][x] == 'A' + length - ft_lst_length(lst) && mode == 2)
		{
			if (first == 0)
			{
				++first;
				map[y][x] = '9';
			}
			else
				map[y][x] = '.';
		}
		++x;
		if (!map[y][x])
		{
			x = 0;
			++y;
		}
	}
}

int		recursive(t_list *lst, char **map, int length, int side)
{
	int res;

	if (!lst)
		return (EXIT_SUCCESS);
	while ((res = find_space(map, (t_piece *)(lst->content))) != -2)
	{
		if (res == EXIT_SUCCESS)
		{
			order_map(map, lst, length, 3);
			order_map(map, lst, length, 1);
			if ((res = recursive(lst->next, map, length, side)) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			ft_dot(map, 2);
			order_map(map, lst, length, 2);
		}
	}
	ft_dot(map, 2);
	order_map(map, lst, length, 3);
	return (EXIT_FAILURE);
}

int		ft_fillit(t_list *lst)
{
	char	**map;
	int		i;
	int result;
	int length;

	length = ft_lst_length(lst);
	result = 0;
	i = ft_sqrt(length * 4);
	map = size_square(i);
	while ((result = recursive(lst, map, length, i)) != EXIT_SUCCESS)
	{
		printf("\n\n\n\n\n\n RESIZE DE LA MAP!\n\n\n\n\n\n\n");
		++i;
		free(map);
		map = size_square(i);
	}
	printf("map finale :\n");
	print_map(map);
	return (EXIT_SUCCESS);
}
