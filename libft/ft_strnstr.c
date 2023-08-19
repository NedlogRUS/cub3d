/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:48:12 by apanikov          #+#    #+#             */
/*   Updated: 2023/02/10 14:55:12 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (needle[n] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		while (haystack[i + n] == needle[n] && needle[n] != '\0' && n + i < len)
			n++;
		if (needle[n] == '\0')
			return ((char *)haystack + i);
		i++;
		n = 0;
	}
	return (0);
}
