/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pushswap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:46:26 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 12:56:55 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Whole program: set environment, read options, read arguments into STACK A,
** sort, print instruction list, free enviroment
*/

int		main(int argc, char **argv)
{
	static ENV e;

	if (!ft_setenv(&e))
		return (display_err(&e));
	e.err.type = 0;
	if (!readarg(&e, argc, argv, 1))
		return (display_err(&e) && freeenv(&e));
	if (e.alen > 1)
	{
		if (!sort(&e))
			return (display_err(&e) && freeenv(&e));
		if (e.ins->lst && (e.fd = 1))
		{
			printlist(&e, e.ins->lst);
			e.fd = 2;
		}
	}
	return (display_err(&e) && freeenv(&e));
}
