/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:30:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 13:04:26 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Assign error codes for error message (see header for possibilities)
*/

int				error(ENV *e, int type, int stack, int msg)
{
	e->err.type = type;
	e->err.msg = msg;
	e->err.stack = stack;
	return (1);
}

/*
** Checks and displays movement error warning (pushing from empty stack or
** rotating single element)
** Input: ins == instruction to check
** Returns 1 for warnings (keep program going) or -2
*/

static int		move_error(ENV *e, int ins)
{
	if ((!e->blen && ins == PA && error(e, WRNG, B, EMPTY))
			|| (!e->alen && ins == PB && error(e, WRNG, A, EMPTY)))
	{
		display_err(e);
		return (1);
	}
	if (e->alen < 2
			&& (ins == RA || ins == RRA || ins == SA
				|| ins == SS || ins == RR || ins == RRR))
	{
		error(e, WRNG, A, NOEFFECT);
		display_err(e);
	}
	if (e->blen < 2
			&& (ins == RB || ins == RRB || ins == SB
				|| ins == SS || ins == RR || ins == RRR))
	{
		error(e, WRNG, B, NOEFFECT);
		display_err(e);
	}
	if (e->err.type == NO_ERR)
		return (0);
	return (-2);
}

/*
** Check and display errors (impossible undo, wrong input, impossible move)
** Input: ins = code of instruction to check, input = string of current
** instruction
** Returns 0 if no error or if run options activated, -1 if error, -2 if undo
** error
*/

int				check_error(ENV *e, int ins)
{
	int		ret;

	ret = NO_ERR;
	if (ins == -2)
	{
		error(e, WRNG, -1, UNDO);
		display_err(e);
		display_options(e, ins, 0);
		error(e, NO_ERR, -1, 0);
		return (-2);
	}
	else if (ins == -1)
	{
		error(e, INPUT, -1, WRONG);
		return (-1);
	}
	ret = move_error(e, ins);
	error(e, NO_ERR, -1, 0);
	if (ret)
		display_options(e, ins, 0);
	return (ret);
}
