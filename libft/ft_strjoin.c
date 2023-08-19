/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:19:30 by apanikov          #+#    #+#             */
/*   Updated: 2023/01/26 17:51:45 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return ((char *)malloc(sizeof(char)));
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	while (s1[a])
	{
		res[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		res[a] = s2[b];
		a++;
		b++;
	}
	res[a] = '\0';
	return (res);
}
