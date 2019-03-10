/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:19:19 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/13 19:43:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** double cast = seule solution trouvee pour silent drop const qualifier error
*/

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_cpy;
	const char	*p;
	char		*ptr;

	p = (const char *)(unsigned long)src;
	ptr = (char *)(unsigned long)p;
	dst_cpy = (char *)dst;
	while (n--)
	{
		*dst_cpy = *ptr;
		dst_cpy++;
		ptr++;
	}
	return (dst);
}
