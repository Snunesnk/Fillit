/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:49:53 by snunes            #+#    #+#             */
/*   Updated: 2019/05/17 20:00:42 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**size_square(int side)
{
	int	i;
	int j;
	char **square;

	i = 0;
	square = (char **)ft_memalloc(sizeof(*square) * side);
	while (i < side)
	{
		j = 0;
		square[i] = (char *)ft_memalloc(sizeof(char) * side);
		while (j < side)
		{
			square[i][j] = '.';
			++j;
		}
		++i;
	}
	return (square);
}

int	ft_findchar(char **tab, char c)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (tab[y][x] != c && tab[y])
	{
		++x;
		if (!tab[y][x])
		{
			++y;
			x = 0;
		}
	}
	return (tab[y][x] == c ? y * ft_strlen(tab[0]) + x : 0);
}

int		space_left(char **square, t_piece *piece, int try)
{
	int x_space;
	int y_space;
	int x_bloc;
	int y_bloc
	int result;

	if (!(result = ft_findchar(square, '.')) && square[0][0] != '.')
		return (0);
	x_space = result % ft_strlen(square[0]);
	y_space = (result - x_space) / ft_strlen(square[0]);
	if (!(result = ft_findchar(piece->tab, '#') && piece->tab[0][0] != '#'))
		return (1);
	x_bloc
	return (0);
}

int		recursive_fill(char **square, t_list *lst)
{
	t_list	*first;
	int		i;
	int try;

	i = 0;
	try = 0;
	first = lst;
	if (!lst)
		return (1);
	while (space_left(square, (t_piece*)(lst->content), try))
	{
		if (recursive_fill(square, lst->next))
			return (1);
		++try;
	}
	return (0);
}

int		ft_fillit(t_list *lst)
{
	int		max_square;
	int		min_square;
	char	**square;
	int		i;

	i  = 2;
	min_square = ft_sqrt(i * 4);
	max_square = 2 * ft_sqrt(i) + 2;
	square = size_square(i);
	while (!recursive_fill(square, lst))
	{
		i++;
		free(square);
		square = size_square(i);
	}
	i = 0;
	while (square[i])
	{
		printf("%s\n", square[i]);
		i++;
	}
	printf("cote du carre = %d\n", i);
	printf("il y a %d tetriminos\nEt on peut mettre les tetrimonos dans un carre de minimum %d et max de %d de cote\n", i, min_square, max_square);
	return (EXIT_SUCCESS);
}
