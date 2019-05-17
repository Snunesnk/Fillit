/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:43:11 by snunes            #+#    #+#             */
/*   Updated: 2019/05/17 18:44:22 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

// permet d'afficher ce qui est demande en cas d'erreur et de quitter proprement
// enfin proprement je sais pas trop
int		ft_error(void)
{
	write(1, "error\n", 6);
	return (0);
}

// alloue de la memoire pour stocker une nouvelle piece
t_piece	*new_piece(void)
{
	int i;
	t_piece	*new_piece;

	i = 0;
	// allocation de memoire pour stocker un tableau
	new_piece = (t_piece*)ft_memalloc(sizeof(t_piece));
	if (!new_piece)
		return (NULL);
	// et voila une nouvelle structure prete a stocker une piece !
	return (new_piece);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_list	lst;
//	t_list	*first;
	int		state;

	state = 0; // temporarire, le temps de faire un fillit
	// comme defini dns le sujet, on affiche l'usage si pas le bon nombre de parametres
	// j'espere que ca passe comme ca
	if (argc != 2)
	{
		write(1, "usage: ./fillit Tetriminos_file\n", 33);
		return (0);
	}
	// protection en cas d'argument null
	if (!argv[1])
		return (ft_error());
	if (!(lst.content = new_piece()))
		return (ft_error());
 	fd = open(argv[1], O_RDONLY);
	// test du fichier passe et stockage des pieces dans la liste
	if (check_file(fd, &lst) == EXIT_FAIL)
		return(ft_error());
	close(fd);
	// state = ft_fillit(first);
	// si on arrive jusque la on peut etre content
	return ((state == -1) ? ft_error() : 0);
}
