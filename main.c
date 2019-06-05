/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:43:11 by snunes            #+#    #+#             */
/*   Updated: 2019/05/31 15:32:41 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_error(t_list *lst, int **coord)
{
	write(1, "error\n", 6);
	if (lst->next && coord)
		free_mem(lst, coord);
	else
	{
		while (lst)
		{
			free(lst->content);
			lst = lst->next;
		}
	}
	return (0);
}

t_piece	*new_piece(t_list *lst)
{
	int		length;
	t_piece	*new_piece;

	length = ft_lst_length(lst);
	new_piece = (t_piece*)ft_memalloc(sizeof(t_piece));
	if (!new_piece)
		return (NULL);
	new_piece->nb = length;
	return (new_piece);
}

int		ft_comp(int **coord, t_piece *tet, t_list *first)
{
	int y;

	while (tet->nb != ((t_piece *)(first->content))->nb)
	{
		y = 0;
		while (ft_strequ(tet->tab[y], ((t_piece *)(first->content))->tab[y]))
		{
			++y;
			if (y == 4)
			{
				coord[tet->nb][0] = ((t_piece *)(first->content))->nb;
				return (1);
			}
		}
		first = first->next;
	}
	coord[tet->nb][0] = tet->nb;
	return (1);
}

int		**define_type(t_list *lst)
{
	int		i;
	int		**coord;
	t_list	*first;

	first = lst;
	i = 0;
	while (lst)
	{
		((t_piece *)(lst->content))->nb = ++i;
		lst = lst->next;
	}
	if (!(coord = (int **)ft_memalloc(sizeof(int *) * (i + 1))))
		return (NULL);
	while (i >= 0 && coord)
	{
		if (!(coord[i--] = (int *)ft_memalloc(sizeof(int) * 3)))
			return (NULL);
	}
	lst = first;
	while (lst && coord)
	{
		ft_comp(coord, ((t_piece *)(lst->content)), first);
		lst = lst->next;
	}
	return (coord);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_list	lst;
	int		**coord;

	lst.next = NULL;
	coord = NULL;
	if (argc != 2)
	{
		write(1, "usage: ./fillit Tetriminos_file\n", 33);
		return (0);
	}
	if (!argv[1])
		return (ft_error(NULL, NULL));
	if (!(lst.content = new_piece(&lst)))
		return (ft_error(NULL, NULL));
	fd = open(argv[1], O_RDONLY);
	if (check_file(fd, &lst) == EXIT_FAILURE)
		return (ft_error(&lst, NULL));
	close(fd);
	if (!(coord = define_type(&lst)) || ft_fillit(&lst, coord) == EXIT_FAILURE)
		return (ft_error(&lst, coord));
	free(lst.content);
	free_mem(lst.next, coord);
	return (0);
}
