/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_opti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 20:48:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 12:58:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Display shortcut in algorithm (switch to insert sort or direct placement of
** min or max integer
** Input: value of max or min integer placed, type = MAX, MIN or INSERTION
*/

int		display_shortcut(ENV *e, int val, int type)
{
	if (!(e->options & OPT_OPTI))
		return (1);
	e->color = COL_OFF;
	e->color = (e->options & OPT_COLOR ? COL_PLACE : e->color);
	e->color = type == INSERTION ? COL_INSERT : e->color;
	ft_putstr_fd(e->color, e->fd);
	if (type == MIN)
		ft_putstr_fd(">>> Shortcut smallest integer: ", e->fd);
	else if (type == MAX)
		ft_putstr_fd(">>> Shortcut biggest integer: ", e->fd);
	if (type != INSERTION)
	{
		ft_putnbr_fd(val, e->fd);
		ft_putchar_fd('\n', e->fd);
	}
	else
		ft_putendl_fd(">>> Shortcut insertion sort", e->fd);
	ft_putstr_fd(COL_OFF, e->fd);
	return (1);
}

/*
** Display optimization pattern | see header for possibilites
** Input: partial instruction list, pat = pattern detected
*/

int		display_pat(ENV *e, t_list *l, int n)
{
	if (!(e->options & OPT_OPTI))
		return (1);
	e->color = COL_OFF;
	while (--n >= 0)
	{
		ft_putstr_fd(e->ins->ref[val(l, n)], e->fd);
		ft_putstr_fd(" ", e->fd);
	}
	ft_putchar_fd('\n', e->fd);
	return (1);
}

/*
** Display rotation optimization
** Input: instruction of rotation detected, n1 = number of instructions removed,
** n2 = number of instructions added
** Note: special case when full rotation instead of inversion rotation,
** instruction remains unchanged instead of opposite, through insvar
*/

int		display_rot(ENV *e, int ins, int n1, int n2)
{
	int	insvar;

	if (!(e->options & OPT_OPTI))
		return (1);
	if (ins < 0)
	{
		ins *= -1;
		insvar = ins;
	}
	else
		insvar = NB_INS - ins - 1;
	if ((e->options & OPT_COLOR))
		e->color = COL_ROT;
	ft_putstr_fd(e->color, e->fd);
	ft_putstr_fd("Rotation         | ", e->fd);
	ft_putstr_fd(COL_OFF, e->fd);
	ft_putnbr_fd(n1, e->fd);
	ft_putchar_fd(' ', e->fd);
	ft_putstr_fd(e->ins->ref[ins], e->fd);
	ft_putstr_fd(" >>> ", e->fd);
	ft_putnbr_fd(n2, e->fd);
	ft_putchar_fd(' ', e->fd);
	ft_putendl_fd(e->ins->ref[insvar], e->fd);
	return (1);
}

/*
** Display mirror optimization
** Input: ins1 and ins2 = instructions removed
*/

int		display_mir(ENV *e, char *ins1, char *ins2)
{
	if (e->options & OPT_OPTI)
	{
		if ((e->options & OPT_COLOR))
			e->color = COL_SYNC;
		ft_putstr_fd(e->color, e->fd);
		ft_putstr_fd("Mirror           | ", e->fd);
		ft_putstr_fd(COL_OFF, e->fd);
		ft_putstr_fd(ins1, e->fd);
		ft_putstr_fd(" ", e->fd);
		ft_putendl_fd(ins2, e->fd);
	}
	return (1);
}

/*
** Display sync optimization
** Input: sync = full optimization string, see #define
*/

int		display_sync(ENV *e, char *sync)
{
	if (e->options & OPT_OPTI)
	{
		if ((e->options & OPT_COLOR))
			e->color = COL_SYNC;
		ft_putstr_fd(e->color, e->fd);
		ft_putstr_fd("Synchronization  | ", e->fd);
		ft_putstr_fd(COL_OFF, e->fd);
		ft_putendl_fd(sync, e->fd);
	}
	return (1);
}
