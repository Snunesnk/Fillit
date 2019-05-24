/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:43:11 by snunes            #+#    #+#             */
/*   Updated: 2019/05/24 19:19:01 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_error(void)
{
	write(1, "error\n", 6);
	return (0);
}

t_piece	*new_piece(t_list *lst)
{
	t_piece	*new_piece;

	new_piece = (t_piece*)ft_memalloc(sizeof(t_piece));
	if (!new_piece)
		return (NULL);
	new_piece->nb = ft_lst_length(lst);
	new_piece->y_size = 0;
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
		++i;
		((t_piece *)(lst->content))->nb = i;
		lst = lst->next;
	}
	coord = (int **)ft_memalloc(sizeof(*coord) * i + 2);
	while (i > 0)
	{
		coord[i] = (int *)ft_memalloc(sizeof(**coord) * 3);
		--i;
	}
	lst = first;
	while (lst)
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
	int		state;
	int		**coord;

	if (argc != 2)
	{
		write(1, "usage: ./fillit Tetriminos_file\n", 33);
		return (0);
	}
	if (!argv[1])
		return (ft_error());
	if (!(lst.content = new_piece(&lst)))
		return (ft_error());
	fd = open(argv[1], O_RDONLY);
	if (check_file(fd, &lst) == EXIT_FAILURE)
		return (ft_error());
	close(fd);
	coord = define_type(&lst);
	state = ft_fillit(&lst, coord);
	return ((state == -1) ? ft_error() : 0);
}
