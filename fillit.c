/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:49:53 by snunes            #+#    #+#             */
/*   Updated: 2019/05/17 18:58:58 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_sqrt(int nb)
{
	int i;

	i = 1;
	while (i * i <= nb)
		++i;
	return (i - 1);
}

char	**size_square(int side)
{
	int	i;
	char **square;

	i = 0;
	square = (char **)ft_memalloc(sizeof(*square) * side);
	while (i < size)
	{
		square[i] = (char *)ft_memalloc(sizeof(char) * size);
		i++;
	}
	return (square);
}

int		space_left

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
	while (space_left(square, lst, try))
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
	char	**square
	int		i;

	i  = 2;
	min_square = ft_sqrt(i * 4);
	max_square = 2 * ft_sqrt(i) + 2;
	square = size_square(i);
	while (!recursive_fill(square, lst, ft_lst_length(lst)))
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
