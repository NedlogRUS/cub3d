/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:21:53 by apanikov          #+#    #+#             */
/*   Updated: 2023/01/31 13:26:22 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	a;

	a = 0;
	if (!dst && !src)
		return (0);
	if (dst != src)
	{
		while (a < n)
		{
			((unsigned char *)dst)[a] = ((unsigned const char *)src)[a];
			a++;
		}
		return (dst);
	}
	return (dst);
}
