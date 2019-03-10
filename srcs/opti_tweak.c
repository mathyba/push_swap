/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_tweak.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:38:57 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 11:20:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Check if possible to relocate or sync first list element
*/

t_list			*gen_sync(ENV *e, t_list **lst, int *opti)
{
	if ((relocate(lst) || sync_ins(e, lst)))
		*opti = 1;
	return (*lst);
}

static int		check_modlen(t_list *l)
{
	int mod;

	mod = 0;
	while (l)
	{
		if (val(l, 0) == PA)
			--mod;
		else if (val(l, 0) == PB)
			++mod;
		l = l->next;
	}
	return (mod);
}

t_list			*tweak_inslist(ENV *e, t_list **l, int *opti)
{
	t_list		*lst;
	int			mod;

	lst = *l;
	mod = check_modlen(*l);
	if (relocate(&lst)
			|| useless_rot(e, &lst, e->alen - mod, e->blen + mod)
			|| (remmir(e, &lst)))
	{
		*opti = 1;
	}
	else if (small_pattern(e, *l, mod, -1) != -1)
		*opti = 1;
	else if (lst
			&& (lst == e->ins->lst || val(lst, 0) != val(lst->prev, 0))
			&& (firstany(lst, RA, RB) || firstany(lst, RRA, RRB))
			&& (lst->next && val(lst, 1) == val(lst, 0))
			&& long_rot(e, &lst, e->alen - mod, e->blen + mod))
		*opti = 1;
	else if (lst && (val(lst, 0) == RA) && e->alen - mod == 2 && (*opti = 1))
		*(int *)lst->content = SA;
	else if (lst && (val(lst, 0) == RB) && e->blen + mod == 2 && (*opti = 1))
		*(int *)lst->content = SB;
	return (lst);
}
