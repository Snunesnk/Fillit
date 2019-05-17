/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:38:19 by snunes            #+#    #+#             */
/*   Updated: 2019/05/17 23:05:26 by snunes           ###   ########.fr       */
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
	// compte le nombre de block trouve
	int block;
	// ligne actuellement lue
	int y;
	// position sur cette ligne
	int x;
	int contact;

	contact = 0;
	block = 0;
	y = 0;
	// tant que l'on a pas parcourue toutes les lignes de la piece
	while (y < 4)
	{
		x = 0;
		// tant que l'on a pas atteint le bout de la ligne
		while (x < 4)
		{
			if (piece->tab[y][x] == '#') //si on trouve un '#'
			{
				++block;
				// on ne checke qu'a partir du deuxieme block trouve,
				//sinon il n'y aura aucun cote commun pour le premier
				contact = contact + count_contact(piece->tab, y, x);
			}
			// si le caractere lu n'est ni un '#' ni un '.'
			else if (piece->tab[y][x] != '.')
				return(EXIT_FAIL);
			++x;
		}
		++y;
	}
	//printf("contact total = %d\n", contact);
	if (contact != 6 && contact != 8)
		return (EXIT_FAIL);
	if (block == 0)
		return (EXIT_SUCCESS);
	return (block == 4 ? EXIT_SUCCESS : EXIT_FAIL);
}

int	check_file(int fd, t_list *list)
{
	// contient la ligne lue
	char	*line;
	int		i;
	int		state;
	t_list	*lst;

	line = NULL;
	i = 0;
	lst = list;
	// tant que le gnl ne renvoie pas d'erreur, que la piece lue n'ai pas plus
	// de 4 lignes et qu la lecture du fichier n'est pas terminee, on lit l'entree
	while ((state = get_next_line(fd, &line)) > 0 && i <= 4)
	{
		// on stocke la ligne lue avec strlcat pour eviter les debordements
		ft_strlcat(((t_piece*)((lst)->content))->tab[i], line, 6);
		// line ne sert plus, et elle n'est pas free dans le get_next_line
		// donc on evite les fuites
		free(line);
		// si la ligne lue ne contient pas 4 caractere et que ce n'est pas une transition
		if (ft_strlen(((t_piece*)((lst)->content))->tab[i]) != 4 && ((t_piece*)((lst)->content))->tab[i][0])
			return (EXIT_FAIL);
		// Si la ligne est vide, c'est surement une transition => '\n' entre deux pieces
		if (!(((t_piece*)((lst)->content))->tab[i][0]))
		{
			// Si transition, on a lu une piece complete, donc on la verifie
			// Si ce n'est pas une transition mais une ligne vide dans le piece,
			// la fonction le detectera.
			if (check_piece((t_piece*)(lst->content)) == EXIT_FAIL)
				return (EXIT_FAIL);
			// c'est bien une transition entre deux pieces, donc on ajoute un maillon
			// dans la liste qui va stocker la piece suivante
			if(!((lst)->next = ft_lstnew(new_piece(), sizeof(t_piece))))
				return (EXIT_FAIL);
			//on avance dans la liste
			lst = (lst)->next;
			i = -1;
		}
		++i;
	}
	// on check le dernier bloc, vu qu'on sort du while des que l'on arrive a la
	// fin du fichier
	if (check_piece((lst)->content) == EXIT_FAIL)
		return (EXIT_FAIL);
	// si il y a une erreur du gnl ou que la piece fasse plus de 4 lignes => erreur
	if (state == -1 || i > 4)
		return (EXIT_FAIL);
	return(EXIT_SUCCESS);
}
