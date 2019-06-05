/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:45:10 by snunes            #+#    #+#             */
/*   Updated: 2019/06/05 20:51:56 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

void	free_map(char **map);
void	free_mem(t_list *lst, int **coord);
int		ft_dot(char **map, int mode, int x, int y);
void	print_map(char **map);
int		find_space(char **map, t_piece *piece, int **pos);
int		check_file(int fd, t_list *lst);
t_piece	*new_piece(t_list *lst);
int		ft_fillit(t_list *lst, int **coord);
#endif
