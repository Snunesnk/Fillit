/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:09:12 by snunes            #+#    #+#             */
/*   Updated: 2019/05/25 16:07:24 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	free_lst(void *content, size_t size)
{
	free(content);
	size = 0;
}

void	free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_mem(t_list *lst, int **coord)
{
	int i;
	int length;

	length = ft_lst_length(lst) + 1;
	i = 0;
	if (*coord)
	{
		while (i <= length || i == 0)
		{
			free(coord[i]);
			i++;
		}
		free(coord);
	}
	if (lst != NULL)
	{
		ft_lstdel(&lst, &free_lst);
		free(lst);
	}
}
