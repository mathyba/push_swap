/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 13:15:07 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 14:01:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Delete one list
*/

static void			del(t_list **list)
{
	t_list *tmp;

	tmp = NULL;
	if (!list || !(*list))
		return ;
	while ((*list))
	{
		tmp = *list;
		*list = (*list)->next;
		ft_memdel((void *)&tmp->content);
		ft_memdel((void **)&tmp);
	}
	ft_memdel((void **)list);
}

/*
** Free lists of general environement
*/

int					freeenv(ENV *e)
{
	del(&e->a);
	del(&e->b);
	del(&e->ins->lst);
	ft_memdel((void **)&e->ins);
	return (1);
}

/*
** Set reference tables for instruction types and fuction + pattern types and
** functions
*/

static void			setinstructions(ENV *e)
{
	static char		p[NB_PAT * 10];
	static char		r[NB_INS * 4];
	static void		(*ins[NB_INS])(ENV *e, t_list **lst) = {
		&pa, &sa, &ra, &rr, &rb, &ss, &rrb, &rrr, &rra, &sb, &pb};
	static t_list	*(*f[NB_PAT])(t_list *lst, int ins1, int ins2, int ins3) = {
		&opti_s2, &opti_s1, &opti_s2, &opti_s2, &opti_rs, &opti_rs, &opti_rs,
		&opti_rs, &opti_rs, &opti_p, &opti_s1, &opti_s1, &opti_rs, &opti_rs,
		&opti_s1, &opti_s1, &opti_s1, &opti_s1, &opti_prr};

	ft_memmove(r, "pa\0\0sa\0\0ra\0\0rr\0\0rb\0\0ss", 22);
	ft_memmove(r + 22, "\0\0rrb\0rrr\0rra\0sb\0\0pb\0\0", 22);
	ft_memmove(p, "sarrasa\0\0\0rasarra\0\0\0rasara\0\0\0rrasarra\0\0", 40);
	ft_memmove(p + 40, "raparra\0\0\0rbpbrrb\0\0\0rbparrb\0\0\0", 30);
	ft_memmove(p + 70, "parrbpb\0\0\0pbrrapa\0\0\0pbsapa\0\0\0\0", 30);
	ft_memmove(p + 100, "sapbra\0\0\0\0sbparb\0\0\0\0pbrapa\0\0\0\0", 30);
	ft_memmove(p + 130, "parbpb\0\0\0\0pasara\0\0\0\0pbsbrb\0\0\0\0", 30);
	ft_memmove(p + 160, "rrasapb\0\0\0rrbsbpa\0\0\0pbrrbpapa", 30);
	ft_memcpy(e->ins->ref, r, 44);
	ft_memcpy(e->op, ins, 88);
	ft_memcpy(e->pattern, p, NB_PAT * 10);
	ft_memcpy(e->opti, f, NB_PAT * sizeof(t_list *));
}

/*
** Set up environment
** Returns true if successful set up | false otherwise
*/

int					ft_setenv(ENV *e)
{
	if (!(e->ins = (INS *)ft_memalloc(sizeof(INS))))
	{
		error(e, PROGRAM, -1, MALLOC);
		return (0);
	}
	setinstructions(e);
	e->ins->lst = NULL;
	e->err.type = NO_ERR;
	e->a = NULL;
	e->b = NULL;
	e->alen = 0;
	e->blen = 0;
	e->fd = 2;
	e->nb_ext = 0;
	e->nb_runs = 1;
	e->options = 0;
	return (1);
}
