/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:49:53 by snunes            #+#    #+#             */
/*   Updated: 2019/05/17 23:23:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**size_square(int side)
{
	int	i;
	int j;
	char **square;

	i = 0;
	if(!(square = (char **)ft_memalloc(sizeof(*square) * side)))
		return (NULL);
	while (i < side && square[i])
	{
		j = 0;
		if (!(square[i] = (char *)ft_memalloc(sizeof(char) * side)))
		{
			while (i)
				free(square[i]);
			free(square);
		}
		while (j < side && square[i][j])
		{
			square[i][j] = '.';
			++j;
		}
		++i;
	}
	i = 0;
	while (square[i])
	{
		printf("%s\n", square[i]);
		i++;
	}
	return (square);
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
	printf("entree recursive\n");
	while (find_space(square, (t_piece*)(lst->content), try))
	{
		printf("ca a trouve de l'espace\n");
		if (recursive_fill(square, lst->next))
			return (1);
		++try;
	}
	return (0);
}

int		ft_fillit(t_list *lst)
{
	int		max_map;
	int		min_map;
	char	**square;
	int		i;

	i  = 2;
	min_map = ft_sqrt(i * 4);
	max_map = 2 * ft_sqrt(i) + 2;
	square = size_square(min_map);
	printf("entree fillit\n");
	while (!recursive_fill(square, lst))
	{
		printf("la recursive a renvoyee 0\n");
		i++;
		free(square);
		if(!(square = size_square(i)))
			return (EXIT_FAIL);
	}
	i = 0;
	while (square[i])
	{
		printf("%s\n", square[i]);
		i++;
	}
	printf("cote du carre = %d\n", i);
	return (EXIT_SUCCESS);
}
