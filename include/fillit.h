/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:45:10 by snunes            #+#    #+#             */
/*   Updated: 2019/05/24 19:14:21 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

# define ABS(x) x > 0 ? x : -x

int		ft_dot(char **map, int mode, int x, int y);
void	print_map(char **map);
int		find_space(char **map, t_piece *piece, int **pos);
int		check_file(int fd, t_list *lst);
t_piece	*new_piece(t_list *lst);
int		ft_fillit(t_list *lst, int **coord);
#endif
