/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:49:53 by snunes            #+#    #+#             */
/*   Updated: 2019/05/18 23:23:54 by snunes           ###   ########.fr       */
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
	return (square);
}

void	print_map(char **map)
{
	int y;

	y = 0;
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
}

int		ft_fillit(t_list *lst)
{
	char	**map;
	int		i;
	int try;
	t_list *first;
	int result;

	first = lst;
	result = 0;
	try = 0;
	i = ft_sqrt(ft_lst_length(lst) * 4) + 1;
	map = size_square(i);
	while (lst)
	{
		printf("map actuelle :\n");
		print_map(map);
		result = find_space(map, (t_piece *)(lst->content), try);
		if (result == -2)
		{
			++i;
			try = 0;
		}
		else if (result == EXIT_FAILURE)
		{
			lst = first;
			free(map);
			map = size_square(i);
			try++;
			printf("try passe a %d\n", try);
		}
		else
			lst = lst->next;
	}
	printf("map finale :\n");
	print_map(map);
	return (EXIT_SUCCESS);
}
