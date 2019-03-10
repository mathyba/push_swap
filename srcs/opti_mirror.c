/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_mirror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:17:45 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 12:16:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Returns true if two first instructions cancel each other
*/

static int	case_mir(t_list *l)
{
	return (twofirstany(l, PA, PB)
			|| twofirstany(l, RA, RRA)
			|| twofirstany(l, RB, RRB)
			|| twofirstany(l, RR, RRR)
			|| twofirst(l, SA, SA)
			|| twofirst(l, SB, SB)
			|| twofirst(l, SS, SS));
}

static void	connect_links(ENV *e, t_list **l)
{
	if ((*l)->next == e->ins->tail)
	{
		(*l)->prev->next = NULL;
		e->ins->tail = (*l)->prev;
		(*l) = e->ins->tail;
	}
	else
	{
		if (!(*l)->prev)
		{
			e->ins->lst = e->ins->lst->next->next;
			e->ins->lst->prev = NULL;
			(*l) = e->ins->lst;
		}
		else
		{
			(*l)->prev->next = ((*l))->next->next;
			if ((*l)->next->next)
				(*l)->next->next->prev = (*l)->prev;
			(*l) = (*l)->next->next;
		}
	}
}

/*
** Apply mirror optimization: Remove two head elements and display opti
** Input: l = partial instructions list, tmp1 and tmp2 are initializers to
** NULL;
*/

t_list		*remmir(ENV *e, t_list **l)
{
	t_list *tmp1;
	t_list *tmp2;

	if (!(*l) || !(*l)->next || !case_mir(*l))
		return (NULL);
	tmp1 = *l;
	tmp2 = (*l)->next;
	connect_links(e, &*l);
	display_mir(e, e->ins->ref[val(tmp1, 0)], e->ins->ref[val(tmp2, 0)]);
	ft_memdel((void **)&tmp1->content);
	ft_memdel((void **)&tmp1);
	ft_memdel((void **)&tmp2->content);
	ft_memdel((void **)&tmp2);
	return (*l);
}
