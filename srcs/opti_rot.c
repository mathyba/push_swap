/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:39:52 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/18 15:59:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Delete one element of partial list, keeping existing links with whole list
** and adjusting pointers to head and tail if necessary
** Input: l = partial instruction list
*/

static void		delete_one_el(ENV *e, t_list **l)
{
	t_list *tmp;

	tmp = (*l);
	if ((*l)->prev)
		(*l)->prev->next = (*l)->next;
	if ((*l)->next)
		(*l)->next->prev = (*l)->prev;
	(*l) = (*l)->next;
	if ((*l) == e->ins->tail)
		e->ins->tail = *l;
	if (*l && !(*l)->prev)
		e->ins->lst = *l;
	ft_memdel((void *)&tmp->content);
	ft_memdel((void *)&tmp);
}

/*
** Apply rotation modification by deleting and replacing elements
** Input: env, l = partial instruction list, len = number of instructions to
** delete, newlen = number of instructions to add
** Returns pointer on list
** Note: rotation type is adjusted with insalt for special case where
** full stack rotation is needed, instead of rotation inversion
*/

static t_list	*rev_rot(ENV *e, t_list **l, int len, int newlen)
{
	int		ins;
	int		insalt;
	int		count;
	t_list	*lst;

	insalt = -1;
	count = 0;
	if (len < 0)
	{
		insalt = val(*l, 0);
		len *= -1;
	}
	ins = NB_INS - val(*l, 0) - 1;
	while (count++ < (int)ft_abs(len - newlen) && *l)
		delete_one_el(e, l);
	count = 0;
	lst = *l;
	while (count++ < newlen && lst)
	{
		*((int *)lst->content) = (insalt != -1 ? insalt : ins);
		lst = lst->next;
	}
	return (lst);
}

/*
** Counts length of serie of identidical instructions and checks if rotation is
** pertinent
** Input: ins = instruction to count, l = partial instruction list,
** mod = length modifier to obtain theoretical stack length
*/

static int		count_serie(ENV *e, int ins, t_list *tmp, int mod)
{
	t_list	*l;
	int		count;

	l = tmp;
	count = 0;
	if ((ins != RA && ins != RB && ins != RRA && ins != RRB)
			|| (l && ins != val(l, 1)))
		return (0);
	while (l && val(l, 0) == ins && ++count)
		l = l->next;
	if (((ins == RA || ins == RRA) && count <= (e->alen - mod) * 0.5)
			|| ((ins == RB || ins == RRB) && count <= (e->blen + mod) * 0.5))
		return (0);
	return (count);
}

/*
** Computes number and type of instructions to launch the rotation and displays
** result
** Input: l = partial instruction list, alen & blen = theoretical len of stacks
*/

static void		switch_rotation(ENV *e, t_list **l, int count, int slen)
{
	int len;
	int	insvar;
	int rtype;
	int ins;

	ins = val(*l, 0);
	insvar = 1;
	if ((rtype = count % slen) > slen * 0.5 && count <= slen)
		len = slen - count % slen;
	else
		len = count % slen;
	if (count > slen && rtype)
		insvar = -1;
	rev_rot(e, l, count > slen && rtype ? -count : count, len);
	if (e->options & OPT_OPTI)
	{
		if (len > rtype && len > slen)
			display_rot(e, insvar * (NB_INS - ins - 1), count, len);
		else
			display_rot(e, insvar * ins, count, len);
	}
}

/*
** If long rotation possible, applies modification on the right stack
** Input: l = partial instruction list, alen and blen = theoretical stack length
** Returns true if rotation | false otherwise
*/

int				long_rot(ENV *e, t_list **l, int alen, int blen)
{
	int count;
	int ins;

	ins = val(*l, 0);
	count = count_serie(e, ins, *l, blen - e->blen);
	if (!count)
		return (0);
	if (count && (ins == RA || ins == RRA))
		switch_rotation(e, l, count, alen);
	else if (count && (ins == RB || ins == RRB))
		switch_rotation(e, l, count, blen);
	else if (count)
		return (0);
	return (1);
}
