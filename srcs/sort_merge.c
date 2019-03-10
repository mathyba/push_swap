/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmerge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:18:58 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 13:11:51 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "limits.h"

/*
** Send integers to STACK A or B according to their value > or <= to median.
** Send directly to end of STACK A (resp. STACK B) if absolute min
** (respect. max) value detected;
** Calls function for decreasing length, stop at null length
*/

static int		splitmed(ENV *e, int dir, int len, int med)
{
	int			ins;
	int			ret;
	static int	push;
	static int	it;

	ret = 0;
	if ((ins = -1) && !len)
	{
		ft_swap(&ret, &push);
		return ((it = 0) + ret);
	}
	else if (dir == A && (ins = (val(e->a, 0) >= med ? RA : PB)) >= 0)
	{
		e->max = (!it ? val(e->a, index_max(e->a, e->alen)) : e->max);
		ins = place_max(e, e->a, e->alen, ins);
	}
	else if (dir == B && (ins = (val(e->b, 0) <= med ? RB : PA)) >= 0)
	{
		e->min = (!it ? val(e->b, index_min(e->b, len)) : e->min);
		ins = place_min(e, e->b, e->blen, ins);
	}
	exe_and_display(e, ins);
	if (++it && (ins == PA || ins == PB))
		++push;
	return (splitmed(e, dir, len - 1, med));
}

/*
** Send lower half of B integers to A, until B small enough to sort by insertion
** Input: **tab of integers to store length of runs stored on, total number of
** runs on stack A, push = number of integers pushed on A this run
** Call recursively until STACK B empty
*/

static int		rec_mergeb(ENV *e, int **runs, int *nb_runs, int push)
{
	if (!e->b)
		return (1);
	if (e->blen < SWITCH_SORT)
	{
		display_shortcut(e, -1, INSERTION);
		e->min = val(e->b, index_min(e->b, e->blen));
		return (rec_insertsortb(e, index_max(e->b, e->blen), e->blen, 0));
	}
	push = splitmed(e, B, e->blen, getmed(e->b, e->blen));
	(*runs)[*nb_runs] = push;
	++(*nb_runs);
	return (rec_mergeb(e, runs, nb_runs, 0));
}

/*
** put either beginning or ending integers from STACK B to STACK A
** Added for norm: recompute min
** Input: len integers to move, part to specify BEG or END integers
*/

static void		put_enda(ENV *e, int len, int part)
{
	if (part == END)
		rrbn(e, &e->ins->lst, len);
	pan(e, &e->ins->lst, len);
	ran(e, &e->ins->lst, len);
	if (part == END)
	{
		e->nb_ext = 0;
		if (e->options & OPT_VERBOSE)
			ft_putendl_fd("\n--- [ SPLIT STACK A ] ---\n", e->fd);
		e->min = val(e->b, index_min(e->b, e->blen));
	}
	else
	{
		if (e->options & OPT_VERBOSE)
			ft_putendl_fd("\n--- [ QUICKSORT STACK B, PUSH BACK TO A ] ---\n",
				e->fd);
		e->min = val(e->a, index_min(e->a, e->runs[e->nb_runs - 1]));
	}
}

/*
** Push next run from STACK A to STACK B, shift directly to end of A is min
** integer is detected;
*/

static void		push_run_to_b(ENV *e)
{
	int	tmpmin;

	while (e->runs[e->nb_runs - 1] > 0)
	{
		if (val(e->a, 0) == e->min && e->nb_runs != 0)
		{
			display_shortcut(e, val(e->a, 0), MIN);
			exe_and_display(e, RA);
			e->min = val(e->a, index_min(e->a, e->runs[e->nb_runs - 1]));
			tmpmin = e->b ? val(e->b, index_min(e->b, e->blen)) : INT_MIN;
			e->min = tmpmin < e->min ? tmpmin : e->min;
		}
		else
			exe_and_display(e, PB);
		--e->runs[e->nb_runs - 1];
	}
}

/*
** Main sorting algo
** Init tab to store length of runs on STACK A
** if STACK A small enough, insert sort | else split in halves around median
** Recursively send lower half of STACK B to STACK A, keeping track of runs
** Push back last run from STACK A to STACK B, until no more runs.
** All the while check for absolute min or max integer to place directly as
** appropriate
*/

int				full_sort(ENV *e)
{
	if (!(e->runs = ft_memalloc(sizeof(int) * ft_ispowtwo(e->alen))))
		return (error(e, PROGRAM, -1, MALLOC) - 1);
	if (e->alen <= SWITCH_SORT)
	{
		display_shortcut(e, -1, INSERTION);
		return (rec_insertsorta(e, index_min(e->a, e->alen), e->alen, 1));
	}
	e->runs[0] = splitmed(e, A, e->alen, getmed(e->a, e->alen)) - e->nb_ext;
	put_enda(e, e->nb_ext, END);
	while (e->nb_runs >= 0)
	{
		rec_mergeb(e, &e->runs, &e->nb_runs, 0);
		e->min = e->b ? val(e->b, index_min(e->b, e->blen)) : e->min;
		put_enda(e, e->blen, BEG);
		if (!e->b && sorted(e, e->a) == 1)
			return (1);
		if (e->nb_runs > 0)
			push_run_to_b(e);
		if (--e->nb_runs >= 0 && e->options & OPT_VERBOSE)
			ft_putendl_fd("\n--- [ NEW RUN ON STACK B ] ---\n", e->fd);
	}
	while (val(e->a, 0) > val(e->a, 1))
		exe_and_display(e, RA);
	return (1);
}
