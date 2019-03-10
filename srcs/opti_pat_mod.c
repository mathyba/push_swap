/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_pat_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:33:14 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/23 18:44:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Delete 3rd instruction, replace 1st instruction by switch
** Invert remaining operations (ex: RAPARRA = PASA)
** Invert again for PARBPB, PBRAPA, PASBPB, PBSAPA patterns
*/

t_list		*opti_rs(t_list *lst, int ins1, int ins2, int ins3)
{
	t_list *tmp;

	(void)ins3;
	*(int *)(lst->content) = (ins1 == RA || ins1 == PA ? SA : SB);
	if (ins1 == PA || ins1 == PB)
		*(int *)(lst->content) = NB_INS - *(int *)lst->content - 1;
	tmp = lst->next;
	lst->next = lst->next->next;
	lst->next->prev = lst;
	*(int *)(lst->next->content) = ins2;
	if ((ins1 == PA && ins2 == RB) || (ins1 == PB && ins2 == RA)
		|| (ins1 == RB && ins2 == PA))
		ft_swap(&*(int *)lst->content, &*(int *)lst->next->content);
	delins(&tmp, NULL);
	return (lst);
}

/*
** Delete first instruction, invert remaining elements (ex: RASARRA = RRASA)
** In case of swap, delete 2nd instruction instead
*/

t_list		*opti_s1(t_list *lst, int ins1, int ins2, int ins3)
{
	t_list *tmp;

	if ((ins2 == SA && ins1 != RA) || (ins2 == SB && ins1 != RB))
		ft_swap(&ins2, &ins1);
	tmp = lst->next;
	(void)ins1;
	*(int *)(lst->content) = ins2;
	lst->next = lst->next->next;
	lst->next->prev = lst;
	*(int *)(lst->next->content) = ins3;
	delins(&tmp, NULL);
	return (lst);
}

/*
** Delete 1st + 3rd instructions, if 2nd is not switch replace by its opposite
** (ex: SARRASA = RA)
*/

t_list		*opti_s2(t_list *lst, int ins1, int ins2, int ins3)
{
	t_list *tmp1;
	t_list *tmp2;

	tmp1 = lst->next;
	tmp2 = lst->next->next;
	(void)ins1;
	(void)ins3;
	if (lst->next->next->next)
	{
		lst->next->next->next->prev = lst;
		lst->next = lst->next->next->next;
	}
	else
	{
		lst->next->next->prev = lst->prev;
		lst->next->next = lst;
		lst->next = NULL;
	}
	if (ins2 == SA || ins2 == SB)
		*(int *)(lst->content) = ins2;
	else
		*(int *)(lst->content) = NB_INS - 1 - ins2;
	delins(&tmp1, &tmp2);
	return (lst);
}

/*
** Bring 3rd instruction as first and replace by opposite instruction
*/

t_list		*opti_p(t_list *lst, int ins1, int ins2, int ins3)
{
	(void)ins3;
	(void)ins1;
	(void)ins2;
	*(int *)(lst->content) = RRA;
	*(int *)(lst->next->content) = SA;
	*(int *)(lst->next->next->content) = RA;
	return (lst);
}

/*
** Handle 4 instructions pattern
*/

t_list		*opti_prr(t_list *lst, int ins1, int ins2, int ins3)
{
	t_list *tmp;

	(void)ins1;
	(void)ins2;
	(void)ins3;
	tmp = lst->next->next->next;
	if (lst->next->next->next->next)
		lst->next->next->next->next->prev = lst->next->next;
	lst->next->next->next = lst->next->next->next->next;
	*(int *)lst->content = SA;
	delins(&tmp, NULL);
	return (lst);
}
