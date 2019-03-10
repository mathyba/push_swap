/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:45:09 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 14:31:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

/*
** Print list str elements starting by last
** Input: list
*/

void		printlist(ENV *e, t_list *l)
{
	t_list	*tmp;
	int		count;

	count = 1;
	tmp = l;
	if (!l)
		return ;
	while (tmp && tmp->next && ++count)
		tmp = tmp->next;
	while (count-- && tmp)
	{
		ft_putendl_fd(e->ins->ref[val(tmp, 0)], e->fd);
		tmp = tmp->prev;
	}
}

/*
** Display error message | see header for possibilities
** Input: type = general error type, stack = where the error is located,
** msg = error details
*/

int			display_err(ENV *e)
{
	static char	*type[TYPE] = {NULL, ERR_WRNG, ERR_PROGRAM, ERR_INPUT,
		ERR_IMP};
	static char	*msg[MSG] = {ERR_ALLOC, ERR_FNCTN, ERR_DUP, ERR_NUM, ERR_EMPTY,
		ERR_EFFECT, ERR_UNDO, ERR_ARG, ERR_RANGE, ERR_WRONG, ERR_OPT};
	static char	*stack[2] = {ERR_STACKA, ERR_STACKB};

	if (e->err.type == NO_ERR)
		return (1);
	e->fd = (e->err.type > 1 && e->checker ? 2 : 1);
	ft_printf("%s", e->err.type != WRNG ? COL_ERR : COL_WRNG);
	if (!(e->options & OPT_COLOR))
		ft_printf("%s", COL_OFF);
	if (e->err.type != WRNG)
		ft_printf("{FD!}Error", &e->fd);
	if (e->options & OPT_VERBOSE)
	{
		if (e->err.type != WRNG)
			ft_printf("{FD!} | ", &e->fd);
		ft_printf("[%s]", (e->err.type >= 0 ? type[e->err.type] : ""));
		ft_printf("%s", COL_OFF);
		ft_printf("%s >>> ", e->err.stack >= 0 ? stack[e->err.stack] : "");
		ft_printf("%s\n", e->err.msg >= 0 ? msg[e->err.msg] : "");
	}
	ft_printf("{EOO}%s", COL_OFF);
	return (-1);
}

/*
** Display one stack (list in input);
*/

static void	show_stack(ENV *e, t_list *s)
{
	t_list	*tmp;
	int		len;

	tmp = s;
	len = list_size(s);
	while (len--)
	{
		ft_putnbr_fd(val(tmp, 0), e->fd);
		if (tmp->next)
			ft_putchar_fd(' ', e->fd);
		tmp = tmp->next;
	}
}

/*
** Display STACK A and STACK B
*/

void		show_stacks(ENV *e)
{
	e->fd = 2;
	if (e->options & OPT_COLOR)
		ft_putstr_fd(COL_STACKA, e->fd);
	if (e->options & OPT_ANIM)
	{
		system("clear");
		system("tput cup 12 1");
	}
	ft_putstr_fd("STACK A", e->fd);
	ft_putstr_fd(" | ", e->fd);
	ft_putstr_fd(COL_OFF, e->fd);
	show_stack(e, e->a);
	ft_putchar_fd('\n', e->fd);
	if (e->options & OPT_ANIM)
		system("tput cup 30 1");
	if (e->options & OPT_COLOR)
		ft_putstr_fd(COL_STACKB, e->fd);
	ft_putstr_fd("STACK B", e->fd);
	ft_putstr_fd(" | ", e->fd);
	ft_putstr_fd(COL_OFF, e->fd);
	show_stack(e, e->b);
	ft_putendl_fd("\n", e->fd);
	if (e->options & OPT_ANIM)
		usleep(80000);
}
