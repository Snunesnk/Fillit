/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:43:11 by snunes            #+#    #+#             */
/*   Updated: 2019/05/22 22:31:38 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_error(void)
{
	write(1, "error\n", 6);
	return (0);
}

t_piece	*new_piece(void)
{
	t_piece	*new_piece;

	new_piece = (t_piece*)ft_memalloc(sizeof(t_piece));
	if (!new_piece)
		return (NULL);
	new_piece->type = 0;
	return (new_piece);
}

void	print_piece(t_list *lst)
{
	int i;

	while (lst)
	{
		i = 0;
		printf("type de cette piece : %d\n", ((t_piece *)(lst->content))->type);
		while (i < 4)
		{
			printf("|%s|\n", ((t_piece*)(lst->content))->tab[i]);
			i++;
		}
		lst = lst->next;
	}
}

void	print_map(char **map)
{
	int y;
	int len;

	len = ft_strlen(map[0]);
	y = 0;
	while (y < len)
	{
		write(1, map[y], len);
		write(1, "\n", 1);
		y++;	
	}
}

int		ft_compare(t_piece *piece, t_list *lst, int *i)
{
	int y;
	int equ;

	while (lst)
	{
		equ = 1;
		y = 0;
		while (y != 4 && equ)
		{
			equ = ft_strequ(piece->tab[y], ((t_piece *)(lst->content))->tab[y]);
			y++;
		}
		if (equ || !lst)
		{
			if (((t_piece *)(lst->content))->type != 0)
				piece->type = ((t_piece *)(lst->content))->type;
			else
			{
				*i = *i + 1;
				piece->type = *i;
			}
			return (EXIT_SUCCESS);
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

int		define_type(t_list *lst)
{
	t_list *first;
	int i;

	i = 0;
	first = lst;
	while (lst)
	{
		ft_compare(((t_piece *)(lst->content)), first, &i);
		lst = lst->next;
	}
	return (i);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_list	lst;
	int		state;
	int		i;
	int 	**coord;

	if (argc != 2)
	{
		write(1, "usage: ./fillit Tetriminos_file\n", 33);
		return (0);
	}
	if (!argv[1])
		return (ft_error());
	if (!(lst.content = new_piece()))
		return (ft_error());
 	fd = open(argv[1], O_RDONLY);
	if (check_file(fd, &lst) == EXIT_FAILURE)
		return(ft_error());
	close(fd);
	i = define_type(&lst);
	coord = (int **)ft_memalloc(sizeof(*coord) * i + 1);
	while (i > 0)
	{
		coord[i] = (int *)ft_memalloc(sizeof(**coord) * 3);
		--i;
	}
	state = ft_fillit(&lst);
	return ((state == -1) ? ft_error() : 0);
}
