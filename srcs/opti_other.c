/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 11:11:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/18 15:58:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Detect if relocation of instruction is possible, if it happens on one stack
** between two operations impacting only the opposite stack
** Return true if relocation | false otherwise
*/

int				relocate(t_list **lst)
{
	t_list		*tmp;
	int			val1;
	int			val2;

	tmp = *lst;
	if (!tmp || !tmp->next)
		return (0);
	val1 = val(tmp, 0);
	val2 = val(tmp, 1);
	if (tmp && tmp->next &&
		(((val1 == RRA || val1 == RRB) && val2 == RRR)
		|| (val1 == RR && (val2 == RA || val2 == RB))
		|| ((val1 == RB) && (val2 == SA || val2 == RRA))
		|| ((val1 == RA) && (val2 == SB || val2 == RRB))
		|| ((val1 == SB) && (val2 == RRA)) || ((val1 == SA) && (val2 == RRB))))
	{
		while (val(*lst, 1) == val2)
		{
			ft_swap(&*(int *)(*lst)->content, &*(int *)(*lst)->next->content);
			*lst = (*lst)->next;
		}
		*lst = tmp;
		return (1);
	}
	return (0);
}

/*
** Detect and correct useless rotation: remove last element
** Input: l = partial instruction lst, alen & blen = theoretical stacks lengh
** Return true if optimization | false otherwise
*/

int				useless_rot(ENV *e, t_list **l, int alen, int blen)
{
	t_list *tmp;

	tmp = (*l)->next;
	if (val(*l, 0) == RR && (blen == 1 || alen == 1))
		*(int *)((*l)->content) = (blen == 1 ? RA : RB);
	else if (((twofirstany(*l, RA, RRA) || val(*l, 0) == SA) && alen < 2)
		|| ((twofirstany(*l, RB, RRB) || val(*l, 0) == SB) && blen < 2))
	{
		if (e->options & OPT_OPTI)
		{
			ft_putstr_fd("Remove ", e->fd);
			ft_putendl_fd(e->ins->ref[val(*l, 0)], e->fd);
		}
		tmp = *l;
		(*l)->next->prev = (*l)->prev;
		if ((*l)->prev)
			(*l)->prev->next = (*l)->next;
		ft_memdel((void **)&tmp->content);
		ft_memdel((void **)&tmp);
	}
	else
		return (0);
	return (1);
}

static void		link_and_del(t_list **l, t_list **tmp, int ins)
{
	if ((*l)->next->next)
		(*l)->next->next->prev = *l;
	(*l)->next = (*l)->next->next;
	*(int *)(*l)->content = ins;
	ft_memdel((void **)&(*tmp)->content);
	ft_memdel((void **)tmp);
}

/*
** Detect and apply sync optimization: remove two elements and replace by
** synchronized instruction
** Input: l = partial instruction lst, tmp = initializer to list->next
** (element to delete), ins = initializer to -1;
** Return true if optimization | false otherwise
*/

int				sync_ins(ENV *e, t_list **l)
{
	t_list	*tmp;
	int		ins;

	ins = -1;
	tmp = (*l)->next;
	if (twofirstany(*l, SA, SB) && display_sync(e, PAT_SASB))
		ins = SS;
	else if (twofirstany(*l, RRA, RR) && display_sync(e, PAT_RRARR))
		ins = RB;
	else if (twofirstany(*l, RRB, RR) && display_sync(e, PAT_RRBRR))
		ins = RA;
	else if (twofirstany(*l, RA, RRR) && display_sync(e, PAT_RARRR))
		ins = RRB;
	else if (twofirstany(*l, RB, RRR) && display_sync(e, PAT_RBRRR))
		ins = RRA;
	else if (twofirstany(*l, RA, RB) && display_sync(e, PAT_RBRRR))
		ins = RR;
	else if (twofirstany(*l, RRA, RRB) && display_sync(e, PAT_RBRRR))
		ins = RRR;
	else
		return (0);
	link_and_del(l, &tmp, ins);
	return (1);
}
