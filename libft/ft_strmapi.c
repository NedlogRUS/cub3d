/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:43:59 by apanikov          #+#    #+#             */
/*   Updated: 2023/02/10 14:56:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*sd;

	i = 0;
	if (!s)
		return (0);
	sd = ft_strdup((char *)(s));
	if (!sd)
		return (sd);
	while (sd[i])
	{
		sd[i] = f(i, sd[i]);
		i++;
	}
	return (sd);
}
