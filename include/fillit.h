/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:45:10 by snunes            #+#    #+#             */
/*   Updated: 2019/05/20 22:12:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

// PENSER A ENLEVER
#include <stdio.h>
// PENSER A ENLEVER

# define ABS(x) x > 0 ? x : -x

int     ft_dot(char **map, int mode);
void	print_map(char **map);
int		find_space(char **map, t_piece *piece);
int		check_file(int fd, t_list *lst);
t_piece	*new_piece(void);
int		ft_fillit(t_list *lst);
#endif
