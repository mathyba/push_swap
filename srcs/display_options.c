/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:24:37 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 13:52:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Display instruction, stack and list if corresponding option selected
** Input: instruction, option = 1 for printing lst, any value for ins and stack
*/

void			display_options(ENV *e, int ins, int option)
{
	int prev;

	prev = e->fd;
	e->fd = 2;
	e->ins_val = ins;
	if (ins > -1)
		if ((e->options) & OPT_INS)
			ft_putendl_fd(e->ins->ref[ins], e->fd);
	if ((e->options) & OPT_STACK || e->options & OPT_ANIM)
		show_stacks(e);
	if (option == 1 && (e->options & OPT_LIST))
		printlist(e, e->ins->lst);
	e->fd = prev;
}

void			exe_and_display(ENV *e, int ins)
{
	e->op[ins](e, &e->ins->lst);
	display_options(e, ins, 0);
}

/*
** Display command list
*/

void			display_commands(ENV *e)
{
	ft_putendl_fd("\tPA : push item from STACK B to STACK A", e->fd);
	ft_putendl_fd("\tPB : push item from STACK A to STACK B", e->fd);
	ft_putendl_fd("\tRA : rotate STACK A forward (first becomes last)", e->fd);
	ft_putendl_fd("\tRB : rotate STACK B forward (first becomes last)", e->fd);
	ft_putendl_fd("\tRR : rotate STACK A and STACK Bforward", e->fd);
	ft_putendl_fd("\tRRA: rotate STACK A backward (last becomes first)", e->fd);
	ft_putendl_fd("\tRRB: rotate STACK B backward (last becomes first)", e->fd);
	ft_putendl_fd("\tRRR: rotate STACK A and STACK B backward", e->fd);
	ft_putendl_fd("\tSA : switch two first items on STACK A", e->fd);
	ft_putendl_fd("\tSB : switch two first items on STACK B", e->fd);
	ft_putendl_fd("\tSS : switch two first items on each stack", e->fd);
	ft_putendl_fd("\tend: launch check", e->fd);
	ft_putendl_fd("\tundo: undo last instruction", e->fd);
}

/*
** Display help
*/

void			display_help(ENV *e)
{
	ft_putstr_fd(COL_CYAN, e->fd);
	ft_putendl_fd("PS usage: ./push_swap -[cfhilos] [integer list]\n", e->fd);
	ft_putstr_fd(COL_LBLUE, e->fd);
	ft_putendl_fd("Checker usage: ./checker -[chilnrsv]", e->fd);
	ft_putendl_fd("Enter one command per line. Available commands:", e->fd);
	display_commands(e);
	ft_putstr_fd(COL_OFF, e->fd);
	ft_putstr_fd("\nList of available options | ", e->fd);
	ft_putendl_fd("PS for push_swap, C for checker", e->fd);
	ft_putendl_fd("\t-a : animate output (C)", e->fd);
	ft_putendl_fd("\t-c : color (PS | C)", e->fd);
	ft_putendl_fd("\t-f : turn of optimization (PS)", e->fd);
	ft_putendl_fd("\t-h : print available options and usage (PS | C)", e->fd);
	ft_putendl_fd("\t-i : print instruction at each step (PS | C)", e->fd);
	ft_putendl_fd("\t-l : print final list (PS | C)", e->fd);
	ft_putendl_fd("\t-n : print number of instructions (C)", e->fd);
	ft_putendl_fd("\t-o : detail optimization found (PS)", e->fd);
	ft_putendl_fd("\t-s : display stacks at each step (PS | C)", e->fd);
	ft_putendl_fd("\t-v : verbose mode (PS | C)", e->fd);
}
