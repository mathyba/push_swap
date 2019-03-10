/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 13:00:25 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/18 16:04:06 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdlib.h>

/*
** Rotate STACK A forward (bring first element to back)
*/

void	ra(ENV *e, t_list **lst)
{
	t_list	*tmp;
	t_list	*head;

	tmp = e->a;
	head = e->a;
	if (e->alen < 2)
		return ;
	add(e, lst, RA);
	e->a = e->a->next;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = head;
	tmp->next->next = NULL;
}

/*
** Rotate STACK B forward (bring first element to back)
*/

void	rb(ENV *e, t_list **lst)
{
	t_list	*tmp;
	t_list	*head;

	tmp = e->b;
	head = e->b;
	if (e->blen < 2)
		return ;
	add(e, lst, RB);
	e->b = e->b->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = head;
	tmp->next->next = NULL;
}

/*
** Rotate both stacks forward (bring first element to back)
*/

void	rr(ENV *e, t_list **lst)
{
	ra(e, lst);
	rb(e, lst);
	remn(lst, 2);
	add(e, lst, RR);
}

/*
** Rotate STACK A forward n times (bring first element to back)
*/

void	ran(ENV *e, t_list **lst, int n)
{
	while (n-- && e->a)
	{
		ra(e, lst);
		display_options(e, RA, 0);
	}
}

/*
** Rotate STACK B forward n times (bring first element to back)
*/

void	rbn(ENV *e, t_list **lst, int n)
{
	while (n-- && e->b)
	{
		rb(e, lst);
		display_options(e, RB, 0);
	}
}
