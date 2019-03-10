/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_opti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 22:10:13 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/11 19:29:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Returns true if first and second list value are ins1 and ins2 in THAT order
*/

int		twofirst(t_list *l, int ins1, int ins2)
{
	if (list_size(l) < 2)
		return (0);
	return (val(l, 0) == ins1 && val(l, 1) == ins2);
}

/*
** Returns true if first and second list value are ins1 and ins2 in ANY order
*/

int		twofirstany(t_list *l, int ins1, int ins2)
{
	return (twofirst(l, ins1, ins2) || twofirst(l, ins2, ins1));
}

/*
** Returns true if first list value is ins1 OR ins2
*/

int		firstany(t_list *l, int ins1, int ins2)
{
	if (!l)
		return (0);
	return (val(l, 0) == ins1 || val(l, 0) == ins2);
}

/*
** Delete one or two elements
*/

void	delins(t_list **t1, t_list **t2)
{
	if (t1)
	{
		ft_memdel((void **)(&(*t1)->content));
		ft_memdel((void **)t1);
	}
	if (t2)
	{
		ft_memdel((void **)(&(*t2)->content));
		ft_memdel((void **)t2);
	}
}
