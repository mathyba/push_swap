/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_pat_detect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:33:44 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 13:53:17 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** Concatenate 4 last instructions in one single string
** Input: l = partial instruction list, seq = to store pattern formed by 4
** first instructions (or "XXX" + 3 instructions), inslen = initializer of
** instruction len to 3
** Returns length of 4th instruction (= 1st in result string), to know by how
**much to move pointer to check patterns of 3 or 4 instructions
*/

static int		retrieve_pat(ENV *e, t_list *l, char *seq, int inslen)
{
	if (list_size(l) > 3)
		inslen = ft_strlen(e->ins->ref[val(l, 3)]);
	ft_bzero(seq, 12);
	if (list_size(l) > 3)
		ft_strlcat(seq, e->ins->ref[val(l, 3)], 12);
	else
		ft_strlcat(seq, "XXX", 12);
	ft_strlcat(seq, e->ins->ref[val(l, 2)], 12);
	ft_strlcat(seq, e->ins->ref[val(l, 1)], 12);
	ft_strlcat(seq, e->ins->ref[val(l, 0)], 12);
	return (inslen);
}

/*
** Compare string with ref pattern table and store number of chars for display
** Input: env, l = partial instruction list, pat = initializer to -1
*/

static int		detect_pattern(ENV *e, t_list *l, int pat)
{
	char	seq[12];
	int		inslen;

	if (list_size(l) < 3)
		return (-1);
	inslen = retrieve_pat(e, l, (char *)seq, 3);
	while (++pat < NB_PAT)
		if (ft_strequ((char *)seq, e->pattern[pat])
				|| ft_strequ((char *)(seq + inslen), e->pattern[pat]))
			return (pat);
	return (-1);
}

/*
** If pattern found and valid, apply corresponding list transformation
** Input: l = partial instruction list, mod = len modifier to obtain
** theoretical len of STACK A and B, pat = initializer to -1
** Returns true if pattern found and replaced | false otherwise
*/

int				small_pattern(ENV *e, t_list *l, int mod, int pat)
{
	int		i;

	if ((pat = detect_pattern(e, l, -1)) != -1
			&& !((pat == 8 && l->prev && val(l->prev, 0) == SA)
				|| (pat <= 3 && e->alen - mod != 3)))
	{
		i = (pat == 17) ? 4 : 3;
		e->color = e->options & OPT_COLOR ? COL_PAT : COL_OFF;
		ft_putstr_fd(e->color, e->fd);
		if (e->options & OPT_OPTI)
			ft_putstr_fd("Pattern          | ", e->fd);
		ft_putstr_fd(COL_OFF, e->fd);
		while (e->options & OPT_OPTI && i--)
		{
			ft_putstr_fd(e->ins->ref[val(l, i)], e->fd);
			ft_putstr_fd(i ? " " : " >>> ", e->fd);
		}
		l = e->opti[pat](l, val(l, 2), val(l, 1), val(l, 0));
		if (pat == 9)
			display_pat(e, l, 3);
		else
			display_pat(e, l, pat == 0 || pat == 2 || pat == 3 ? 1 : 2);
		return (pat);
	}
	return (-1);
}
