/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:43:11 by snunes            #+#    #+#             */
/*   Updated: 2019/05/21 16:50:46 by snunes           ###   ########.fr       */
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
	return (new_piece);
}

void	print_piece(t_list *lst)
{
	int i;

	while (lst)
	{
		i = 0;
		while (i < 5)
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

int		main(int argc, char **argv)
{
	int		fd;
	t_list	lst;
	int		state;

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
	state = ft_fillit(&lst);
	return ((state == -1) ? ft_error() : 0);
}
