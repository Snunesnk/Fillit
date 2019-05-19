/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:38:19 by snunes            #+#    #+#             */
/*   Updated: 2019/05/18 21:44:05 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

// verifie que chaque bloc possede un cote commun avec un autre bloc
int		count_contact(char tab[5][5], int y, int x)
{
	int contact;

	contact = 0;
	// verifie qu'il n'y ait pas plus de 4 blocs
	//check si il y a un bloc en haut
	if (y - 1 >= 0 && tab[y - 1][x] == '#')
		++contact;
	//check si il y a un bloc a gauche
	if (x - 1 >= 0 && tab[y][x - 1] == '#')
		++contact;
	//check si il y a un bloc a droite
	if (x + 1 < 4 && tab[y][x + 1] == '#')
		++contact;
	// check block en bas
	if (y + 1 < 4 && tab[y + 1][x] == '#')
		++contact;
	return (contact);
}

// verifie que chaque piece recue soit valide
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
				contact = contact + count_contact(piece->tab, y, x);
			}
			else if (piece->tab[y][x] != '.')
				return(EXIT_FAILURE);
		}
	}
	if ((contact != 6 && contact != 8) || (block != 0 && block != 4))
		return (EXIT_FAILURE);
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
			printf("piece verifiee\n");
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
