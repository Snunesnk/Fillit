/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:38:19 by snunes            #+#    #+#             */
/*   Updated: 2019/05/31 16:07:21 by snunes           ###   ########.fr       */
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
		if (tab[y][x] == '#')
			tab[y][x] = '.';
		++x;
		if (x == 4)
		{
			++y;
			x = 0;
		}
	}
}

int		arrange_piece(t_piece *piece, int x, int y)
{
	y = (x == 4) ? y + 1 : y;
	x = (x == 4) ? 0 : x;
	if (y == 4)
	{
		clean_tab(piece->tab);
		return (EXIT_SUCCESS);
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

int		check_piece(t_piece *piece)
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
			if (piece->tab[y][x] == '#')
			{
				++block;
				contact = contact + count_contact(piece, y, x, block);
			}
			else if (piece->tab[y][x] != '.')
				return (EXIT_FAILURE);
		}
	}
	if ((contact != 6 && contact != 8) || (block != 0 && block != 4) || y != 4)
		return (EXIT_FAILURE);
	return (arrange_piece(piece, 0, 0));
}

int		check_file(int fd, t_list *lst)
{
	char	*line;
	int		i;
	int		state;

	line = NULL;
	i = 0;
	while ((state = get_next_line(fd, &line)) > 0 && ft_strlen(line) <= 4)
	{
		ft_strcpy(((t_piece *)(lst->content))->tab[i], line);
		free(line);
		if (i++ == 4)
		{
			if (check_piece((t_piece *)(lst->content)) == EXIT_FAILURE
					|| !(lst->next = ft_lstnew(NULL, 0))
					|| !(lst->next->content = new_piece(lst)))
				return (EXIT_FAILURE);
			lst = lst->next;
			i = 0;
		}
	}
	free(line);
	if (check_piece((lst)->content) == EXIT_FAILURE || state == -1 || i != 4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
