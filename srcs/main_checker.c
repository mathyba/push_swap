/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:46:26 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 14:21:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Check if STACK B empty and STACK A ordered, display success or failure
*/

static void		checkorder(ENV *e)
{
	e->fd = STDOUT;
	if (sorted(e, e->a) == 1 && !e->blen)
	{
		if (e->options & OPT_LIST)
			printlist(e, e->ins->lst);
		if (e->options & OPT_COLOR)
			ft_printf("%s%s%s\n", COL_OK, SUCCESS, COL_OFF);
		else
			ft_printf("OK\n");
	}
	else
	{
		if (e->options & OPT_LIST)
			printlist(e, e->ins->lst);
		if (e->options & OPT_COLOR)
			ft_printf("%s%s%s\n", COL_KO, FAILURE, COL_OFF);
		else
			ft_printf("KO\n");
	}
}

/*
** Finds and returns instruction to apply (opposite of instruction if undo)
** Input: str = current instruction, undo = marker to keep track of number of
** undos (and hom many instructions to check backward)
** Return -1 if no valid instruction, -2 if final undo reached
*/

static int		matchins(ENV *e, char *str, int *undo)
{
	int	lastins;
	int index;

	if (ft_strequ("undo", str) && e->ins->lst)
	{
		*undo = 1;
		lastins = val(e->ins->lst, 0);
		if (lastins == SA || lastins == SB || lastins == SS)
			return (lastins);
		return (NB_INS - lastins - 1);
	}
	*undo = 0;
	index = -1;
	while (++index < NB_INS)
		if (ft_strequ((e->ins->ref[index]), str))
			return (index);
	return (-1);
}

/*
** Display instruction count if option activated
*/

static int		display_count(ENV *e)
{
	if (e->options & OPT_NUM && (e->color = COL_NUM))
	{
		ft_printf("%sNumber of instructions: ", e->color);
		ft_printf("%d%s\n", list_size(e->ins->lst), COL_OFF);
	}
	return (1);
}

/*
** Read instructions on STDIN, find and apply instruction to stacks
** Input: ins = initializer to NULL, undo = unitializer to 0,
** index = initializer
** Return value of check_error, or 0 if successful
*/

static int		readinstructions(ENV *e, char *ins, int undo, int index)
{
	int		ret;
	int		err;

	e->ins->lst = NULL;
	e->fd = STDIN;
	while ((ret = get_next_line2(STDIN, &ins) > 0) && ins)
	{
		index = matchins(e, ins, &undo);
		if (ft_strequ(ins, "end") || (err = check_error(e, index)) == -1)
		{
			ft_strdel(&ins);
			return (err);
		}
		if (err != -2)
		{
			e->op[index](e, &e->ins->lst);
			if (undo == 1)
				remn(&e->ins->lst, 2);
			if (err == 0)
				display_options(e, index, 0);
		}
		ft_strdel(&ins);
	}
	ft_strdel(&ins);
	return (display_count(e));
}

/*
** Checker program
** Set end, read options, read instructions, check order, display result
*/

int				main(int argc, char **argv)
{
	ENV		e;

	if (argc > 1 && (e.checker = 1))
	{
		if (!ft_setenv(&e))
			return (display_err(&e));
		if (!readarg(&e, argc, argv, 1))
			return (display_err(&e) && freeenv(&e));
		if (e.options & OPT_STACK)
			show_stacks(&e);
		if (readinstructions(&e, NULL, 0, -1) == -1)
			return (display_err(&e) && freeenv(&e));
		checkorder(&e);
		display_err(&e);
		freeenv(&e);
	}
	return (-1);
}
