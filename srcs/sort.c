/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:24:34 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 12:29:15 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Move cursor according to optimizations: don't move if list modified, move
** to next instruction if list not modified, back to beginning if at least
** one optimization on last run
** Input: partial instruction list, pointer on opti boolean (relative to last
** instruction, pointer on change boolean (relative to whole list, if at least
** one opti)
*/

static int		move_cursor(ENV *e, t_list **lst, int *opti, int *change)
{
	if (*lst && *lst != e->ins->lst)
	{
		if (*opti == 0)
			*lst = (*lst)->prev;
		else if (*opti == 1 && (*change = 1))
			*opti = 0;
	}
	else if (*change == 1 || *opti == 1)
	{
		*opti = 0;
		*change = 0;
		*lst = e->ins->tail;
	}
	else
		return (0);
	return (1);
}

/*
** Params: env, pointer on scanning function
** Call scanning function until cursor reaches end of instruction list
*/

static int		opti_scan(ENV *e, t_list *(*f)(ENV *e, t_list **l, int *opti))
{
	int		opti;
	t_list	*l;
	int		change;

	change = 0;
	opti = 0;
	l = e->ins->tail;
	while (l != e->ins->lst->prev && e->ins->lst && e->ins->lst->next)
	{
		l = f(e, &l, &opti);
		if (!move_cursor(e, &l, &opti, &change))
			return (0);
	}
	return (1);
}

/*
** Split initial list in two, apply alternative merge on each stack, scan for
** all optimization except sync, last scan for sync optimization
*/

int				sort(ENV *e)
{
	int ret1;
	int	ret2;

	ret1 = 1;
	ret2 = 1;
	e->alen = list_size(e->a);
	if (e->options & OPT_STACK)
		show_stacks(e);
	if (!e->a || (sorted(e, e->a) > 0))
		return (1);
	full_sort(e);
	e->ins->tail = ft_lstget_last(e->ins->lst);
	while ((ret1 || ret2) && !(e->options & OPT_OFF)
			&& e->ins->lst && e->ins->lst->next)
	{
		ret1 = opti_scan(e, &tweak_inslist);
		ret2 = opti_scan(e, &gen_sync);
		if (e->options & OPT_VERBOSE && (ret1 || ret2))
			ft_putendl_fd("\n[ SCAN AGAIN FOR OPTIMIZATION ]\n", e->fd);
	}
	return (1);
}
