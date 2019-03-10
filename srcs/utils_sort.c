/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 22:55:17 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 13:50:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Scans list of integer, stores in tab and returns median value
** Input: list, size = length of list
*/

int	getmed(t_list *l, int size)
{
	int		*tab;
	t_list	*tmp;
	int		i;
	int		len;
	int		ret;

	i = 0;
	tmp = l;
	len = size;
	tab = ft_memalloc(sizeof(int) * size);
	while (len--)
	{
		tab[i] = *(int *)tmp->content;
		tmp = tmp->next;
		++i;
	}
	ft_sort_int_tab(tab, size);
	ret = tab[(int)((size + 1) * 0.5)];
	ft_memdel((void **)&tab);
	return (ret);
}

int	sorted(ENV *e, t_list *tmp)
{
	(void)e;
	if (!tmp || !tmp->next)
		return (1);
	if (*(int *)tmp->content < *(int *)tmp->next->content)
	{
		while (tmp->next && *(int *)tmp->next->content > *(int *)tmp->content)
			tmp = tmp->next;
		return (tmp->next ? 0 : 1);
	}
	else
	{
		while (tmp->next && *(int *)tmp->next->content < *(int *)tmp->content)
			tmp = tmp->next;
		return (tmp->next ? -1 : 0);
	}
}
