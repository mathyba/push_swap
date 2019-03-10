/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:37:18 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/18 16:04:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Swap two first elements of STACK A
*/

void		sa(ENV *e, t_list **lst)
{
	if (e->alen < 2)
		return ;
	add(e, lst, SA);
	ft_swap((int *)e->a->content, (int *)e->a->next->content);
}

/*
** Swap two first elements of STACK B
*/

void		sb(ENV *e, t_list **lst)
{
	if (e->blen < 2)
		return ;
	add(e, lst, SB);
	ft_swap((int *)e->b->content, (int *)e->b->next->content);
}

/*
** Swap two first elements of STACK A and two first elements of STACK B
*/

void		ss(ENV *e, t_list **lst)
{
	sa(e, lst);
	sb(e, lst);
	remn(lst, 2);
	add(e, lst, SS);
}
