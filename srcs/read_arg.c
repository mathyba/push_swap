/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:58:20 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 15:04:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdlib.h>

/*
** Store integers in tab, sort and check if duplicates
** Input: size = length of STACK A
** Returns 1 if duplicate, 0 otherwise
*/

static int			check_dup(ENV *e, int size)
{
	int		*tab;
	int		i;
	t_list	*tmp;
	int		ret;

	tmp = e->a;
	i = 0;
	if (!(tab = ft_memalloc(size * sizeof(int))))
	{
		error(e, PROGRAM, -1, MALLOC);
		return (0);
	}
	while (tmp)
	{
		tab[i++] = *(int *)tmp->content;
		tmp = tmp->next;
	}
	ret = ft_sort_inttab_nodup(tab, size);
	ft_memdel((void **)&tab);
	return (ret);
}

/*
**Converts string instruction to int and add to STACK A
** Input: str = tab of all strings of one argument, size of tab
** Returns true if successfully added | false otherwise
*/

static int			add_int_to_stack(ENV *e, char **str, int size)
{
	int			val;
	t_list		*new;

	new = NULL;
	while (size--)
	{
		if (ft_beyond_limiti(str[size]) && error(e, INPUT, -1, RANGE))
			return (0);
		if (!is_number(str[size]) && error(e, INPUT, -1, NUMBER))
			return (0);
		val = ft_atoi(str[size]);
		new = ft_lstnew(&val, sizeof(int *));
		ft_lstadd(&e->a, new);
		ft_strdel(&str[size]);
		++e->alen;
	}
	if (!check_dup(e, e->alen) && error(e, INPUT, -1, DUP))
		return (0);
	return (1);
}

static void			free_tab(char ***tab, int size)
{
	int i;

	i = -1;
	while (++i < size)
		ft_strdel(&(*tab)[i]);
	ft_memdel((void **)&(*tab));
}

/*
** Read options, read and split remaining arguments (= integers to sort)
** Input: argc, argv, stop for initialization to 0
** Return true if all arguments valid | false otherwise
*/

int					readarg(ENV *e, int argc, char **argv, int stop)
{
	char			**cut;
	int				arg;
	int				size;

	arg = argc - 1;
	if ((!(cut = NULL) && argc <= 1 && error(e, WRNG, -1, NOARG))
		|| read_options(e, argv, argc, &stop) < 0 || e->options == -1
		|| (stop == -1 && error(e, WRNG, -1, NOARG)))
		return (0);
	while (arg >= stop && !(size = 0))
	{
		if ((cut = ft_strsplit(argv[arg], ' ')) == NULL)
			return (error(e, PROGRAM, -1, FUNCTION) - 1);
		if ((size = ft_get_strtabsize(cut)) && !add_int_to_stack(e, cut, size))
		{
			free_tab(&cut, size);
			return (0);
		}
		--arg;
		free_tab(&cut, size);
	}
	return (1);
}
