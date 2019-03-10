/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:30:51 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 12:37:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int			rec_insertsorta(ENV *e, int next, int len, int beg)
{
	static int push;

	if (beg)
		push = 0;
	if (!len)
	{
		pan(e, &e->ins->lst, push);
		return (1);
	}
	if (next > 0)
	{
		e->op[RA](e, &e->ins->lst);
		display_options(e, RA, 0);
		return (rec_insertsorta(e, next - 1, len, 0));
	}
	else if (!next && ++push)
	{
		e->op[PB](e, &e->ins->lst);
		display_options(e, PB, 0);
		return (rec_insertsorta(e, next - 1, len - 1, 0));
	}
	else if (next == -1)
		return (rec_insertsorta(e, index_min(e->a, len), len, 0));
	return (rec_insertsorta(e, next, len, 0));
}

static int	handle_min(ENV *e, int next, int *push, int len)
{
	int		tmpmin;

	display_shortcut(e, val(e->a, 0), MIN);
	exe_and_display(e, PA);
	exe_and_display(e, RA);
	e->min = e->b ? val(e->b, index_min(e->b, e->blen)) : e->min;
	tmpmin = val(e->a, index_min(e->a, *push));
	if (tmpmin < e->min)
		e->min = tmpmin;
	return (rec_insertsortb(e, next, len - 1, *push - 1));
}

int			rec_insertsortb(ENV *e, int next, int len, int push)
{
	if (!len)
	{
		pbn(e, &e->ins->lst, push);
		return (1);
	}
	if (next > 0)
	{
		exe_and_display(e, RB);
		return (rec_insertsortb(e, next - 1, len, push));
	}
	else if (!next && ++push)
	{
		if (val(e->b, 0) == e->min && ++e->nb_ext)
			return (handle_min(e, next, &push, len));
		else
			exe_and_display(e, PA);
		return (rec_insertsortb(e, next - 1, len - 1, push));
	}
	else if (next == -1)
		return (rec_insertsortb(e, index_max(e->b, len), len, push));
	return (rec_insertsortb(e, next, len, push));
}
