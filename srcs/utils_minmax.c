/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 22:55:17 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 12:49:53 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int			index_max(t_list *l, int len)
{
	int		imax;
	int		max;
	int		minlen;
	int		i;

	imax = 0;
	if (!l)
		return (-1);
	if (len > (minlen = list_size(l)))
		len = minlen;
	max = val(l, 0);
	i = -1;
	while (++i < len)
		if (val(l, i) > max)
		{
			imax = i;
			max = val(l, imax);
		}
	return (imax);
}

int			index_min(t_list *l, int len)
{
	int		imin;
	int		min;
	int		minlen;
	int		i;

	i = 0;
	imin = 0;
	if (!l)
		return (-1);
	if (len > (minlen = list_size(l)))
		len = minlen;
	min = val(l, 0);
	while (i < len)
	{
		if (val(l, i) < min)
		{
			imin = i;
			min = val(l, imin);
		}
		++i;
	}
	return (imin);
}

/*
** Checks if first int on STACK A is absolute max, place at end of B if so.
** Input: stack, length of stack, ins to apply if not max int
** Returns rot ins for follow-up in calling function, else previously computed
** ins
*/

int			place_max(ENV *e, t_list *l, int len, int ins)
{
	if (val(l, 0) == e->max)
	{
		++e->nb_ext;
		display_shortcut(e, val(l, 0), MAX);
		exe_and_display(e, PB);
		e->max = val(l, index_max(l, len));
		return (RB);
	}
	return (ins);
}

/*
** Checks if first int on stack is absolute min, place at end of A if so.
** Input: stack, length of stack, ins to apply if not max int
** Returns rot ins for follow-up in calling function, else previously computed
** ins
*/

int			place_min(ENV *e, t_list *l, int len, int ins)
{
	if (val(l, 0) == e->min)
	{
		display_shortcut(e, val(l, 0), MIN);
		exe_and_display(e, PA);
		e->min = val(l, index_min(l, len));
		return (RA);
	}
	return (ins);
}
