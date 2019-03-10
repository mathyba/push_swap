/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:32:57 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/19 19:33:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdlib.h>

/*
** Push one instruction from STACK B to STACK A
*/

void	pa(ENV *e, t_list **lst)
{
	t_list *tmp;

	tmp = e->b;
	add(e, lst, PA);
	if (!e->b)
		return ;
	++e->alen;
	--e->blen;
	if (!e->a)
	{
		e->a = tmp;
		e->b = tmp->next;
		e->a->next = NULL;
		return ;
	}
	e->b = e->b->next;
	tmp->next = e->a;
	e->a = tmp;
}

/*
** Push one instruction from STACK A to STACK B
*/

void	pb(ENV *e, t_list **lst)
{
	t_list *tmp;

	add(e, lst, PB);
	if (!e->a)
		return ;
	++e->blen;
	--e->alen;
	if (!e->b)
	{
		e->b = e->a;
		e->a = e->a->next;
		e->b->next = NULL;
		return ;
	}
	tmp = e->a;
	e->a = e->a->next;
	tmp->next = e->b;
	e->b = tmp;
}

/*
** Push n instructions from STACK A to STACK B
*/

void	pbn(ENV *e, t_list **lst, int n)
{
	while (n-- && e->a)
	{
		pb(e, lst);
		display_options(e, PB, 0);
	}
}

/*
** Push n instructions from STACK B to STACK A
*/

void	pan(ENV *e, t_list **lst, int n)
{
	while (n-- && e->b)
	{
		pa(e, lst);
		display_options(e, PA, 0);
	}
}
