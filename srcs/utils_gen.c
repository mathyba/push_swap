/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 22:09:33 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/23 15:30:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Returns list size
*/

int		list_size(t_list *lst)
{
	t_list	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp && ++count)
		tmp = tmp->next;
	return (count);
}

/*
** Returns value of lst at position "pos"
*/

int		val(t_list *lst, int pos)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp && tmp->next && i++ < pos)
		tmp = tmp->next;
	return (*(int *)tmp->content);
}

/*
** Checks if all chars of a string are digits, except - for negative values
*/

int		is_number(char *str)
{
	if (*str == '-')
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
