/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:05:45 by apanikov          #+#    #+#             */
/*   Updated: 2023/02/09 17:17:50 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*res;

	if (!s)
		return (0);
	i = start;
	if (i > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	i = ft_strlen(&s[i]);
	if (len > ft_strlen(s) - start)
		len = (ft_strlen(s) - start);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	j = 0;
	i = start;
	while (s[i] != '\0' && j < len)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
