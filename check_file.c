/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:38:19 by snunes            #+#    #+#             */
/*   Updated: 2019/05/22 22:25:26 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	clean_tab(char tab[5][5])
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < 4)
	{
		++x;
		if (x == 4)
		{
			++y;
			x = 0;
		}
		if (tab[y][x] == '#')
			tab[y][x] = '.';
	}
}
int		arrange_piece(t_piece *piece, int x, int y)
{
	if (x == 4)
	{
		x = 0;
		++y;
		if (y > 3)
		{
			clean_tab(piece->tab);
			return (EXIT_SUCCESS);
		}
	}
	if (piece->tab[y][x] == '#')
	{
		if (y - piece->y_first >= 0 && x - piece->x_first >= 0)
		{
			if (arrange_piece(piece, x + 1, y) == EXIT_SUCCESS)
			{
				piece->tab[y - piece->y_first][x - piece->x_first] = '#';
				return (EXIT_SUCCESS);
			}
			else
			{
				piece->x_first -= 1;
				return (arrange_piece(piece, x, y));
			}
		}
		else
			return (EXIT_FAILURE);
	}
	return (arrange_piece(piece, x + 1, y));
}
int		count_contact(t_piece *piece, int y, int x, int block)
{
	int contact;

	contact = 0;
	if (block == 1)
	{
		piece->y_first = y;
		piece->x_first = x;
	}
	if (y - 1 >= 0 && piece->tab[y - 1][x] == '#')
		++contact;
	if (x - 1 >= 0 && piece->tab[y][x - 1] == '#')
		++contact;
	if (x + 1 < 4 && piece->tab[y][x + 1] == '#')
		++contact;
	if (y + 1 < 4 && piece->tab[y + 1][x] == '#')
		++contact;
	return (contact);
}

int	check_piece(t_piece *piece)
{
	int block;
	int y;
	int x;
	int contact;

	contact = 0;
	block = 0;
	y = -1;
	while (piece->tab[++y][0])
	{
		x = -1;
		while (x++ < 3)
		{
			if (piece->tab[y][x] == '#') //si on trouve un '#'
			{
				++block;
				contact = contact + count_contact(piece, y, x, block);
			}
			else if (piece->tab[y][x] != '.')
				return(EXIT_FAILURE);
		}
	}
	if ((contact != 6 && contact != 8) || (block != 0 && block != 4))
		return (EXIT_FAILURE);
	arrange_piece(piece, 0, 0);
	return (EXIT_SUCCESS);
}

int	check_file(int fd, t_list *lst)
{
	char	*line;
	int		i;
	int		state;

	line = NULL;
	i = 0;
	while ((state = get_next_line(fd, &line)) > 0)
	{
		if (ft_strlen(line) == 4)
			ft_strcpy(((t_piece *)(lst->content))->tab[i], line);
		free(line);
		if (i == 4)
		{
			if (check_piece((t_piece *)(lst->content)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (!(lst->next = ft_lstnew(new_piece(), sizeof(t_piece *))))
				return (EXIT_FAILURE);
			lst = lst->next;
			i = -1;
		}
		++i;
	}
	if (check_piece((lst)->content) == EXIT_FAILURE || state == -1)
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}
