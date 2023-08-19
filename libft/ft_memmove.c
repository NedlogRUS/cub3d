/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:34:41 by apanikov          #+#    #+#             */
/*   Updated: 2023/01/31 14:51:50 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned const char	*s;
	unsigned char		*d;
	size_t				i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned const char *)src;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		i = len - 1;
		while (i < len)
		{
			d[i] = s[i];
			i--;
		}
		return (dst);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
