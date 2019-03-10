/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_rr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:33:23 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/18 19:33:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdlib.h>

/*
** Rotate STACK A backwards (bring last element to front)
*/

void	rra(ENV *e, t_list **lst)
{
	t_list *tmp;

	tmp = e->a;
	if (e->alen < 2)
		return ;
	add(e, lst, RRA);
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next->next = e->a;
	e->a = tmp->next;
	tmp->next = NULL;
}

/*
** Rotate STACK B backwards (bring last element to front)
*/

void	rrb(ENV *e, t_list **lst)
{
	t_list *tmp;

	tmp = e->b;
	if (e->blen < 2)
		return ;
	add(e, lst, RRB);
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next->next = e->b;
	e->b = tmp->next;
	tmp->next = NULL;
}

/*
** Rotate both stacks backwards (bring last element to front)
*/

void	rrr(ENV *e, t_list **lst)
{
	rra(e, lst);
	rrb(e, lst);
	remn(lst, 2);
	add(e, lst, RRR);
}

/*
** Rotate STACK A backwards n times (bring last element to front)
*/

void	rran(ENV *e, t_list **lst, int n)
{
	while (n-- && e->a)
	{
		rra(e, lst);
		display_options(e, RRA, 0);
	}
}

/*
** Rotate STACK B backwards n times (bring last element to front)
*/

void	rrbn(ENV *e, t_list **lst, int n)
{
	while (n-- && e->b)
	{
		rrb(e, lst);
		display_options(e, RRB, 0);
	}
}
