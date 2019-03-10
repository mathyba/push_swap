/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:35:25 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/18 16:10:01 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Remove n elements from beginning of list
*/

void	remn(t_list **lst, int n)
{
	while (n--)
		rem(lst);
}

/*
** Remove n elements and add one element (beginning of list);
*/

void	remn_add(ENV *e, t_list **lst, int n, int ins)
{
	remn(lst, n);
	add(e, lst, ins);
}

/*
** Add one element to beginning of list
*/

void	add(ENV *e, t_list **lst, int ins)
{
	t_list *new;

	if (!e->checker && *lst && (*lst)->next)
	{
		useless_rot(e, &e->ins->lst, e->alen, e->blen);
		if (*lst && (*lst)->next)
			remmir(e, &e->ins->lst);
		if (lst && *lst)
			relocate(lst);
	}
	new = ft_lstnew(&ins, sizeof(int *));
	ft_lstadd(lst, new);
}

/*
** Add n elements to beginning of list
*/

void	addn(ENV *e, t_list **lst, int n, int ins_ref)
{
	while (n-- > 0)
		add(e, lst, ins_ref);
}

/*
** Remove first element from list
*/

void	rem(t_list **lst)
{
	t_list *head;

	if (!(*lst))
		return ;
	if (!(*lst)->next)
	{
		ft_memdel((void **)(&(*lst)->content));
		ft_memdel((void **)lst);
		return ;
	}
	if ((*lst)->prev)
		(*lst)->next->prev = (*lst)->prev;
	head = *lst;
	*lst = (*lst)->next;
	ft_memdel((void **)&head->content);
	ft_memdel((void **)&head);
}
