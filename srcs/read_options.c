/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:50:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 14:53:49 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int			is_option(ENV *e, char c)
{
	if (ft_isalpha(c) || !c)
	{
		if (!ft_strchr("cdfhilnorsva", c))
		{
			error(e, INPUT, -1, OPTION);
			return (0);
		}
		return (1);
	}
	return (0);
}

/*
** Read arguments starting with -, modify binary tracker
** Input: argv, argc, pointer on number of arguments counted as options
** Note: num is to adjust number arguments read as input
** Returns -1 if option error, otherwise 1. Options value is stored in env
*/

int					read_options(ENV *e, char **argv, int argc, int *num)
{
	int arg;
	int i;
	int ret;
	int	options;

	options = 0;
	if ((arg = 1) && !argv[1][0])
		return (-1);
	while (argv[arg][0] == '-' && is_option(e, argv[arg][1]) && --argc)
	{
		if ((i = 1) && argv[arg][0] == '-' && !argv[arg][1])
			return (-error(e, INPUT, -1, OPTION));
		while ((ret = is_option(e, argv[arg][i])) == 1)
		{
			options |= (1 << (argv[arg][i] - 'a'));
			++i;
		}
		if (++arg && ret < 0)
			return (-1);
		if (++(*num) && argc == 1 && (*num = -1))
			break ;
	}
	if (((e->options = options) & OPT_HELP))
		display_help(e);
	return (1);
}
