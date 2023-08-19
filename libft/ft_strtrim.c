/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:00:14 by apanikov          #+#    #+#             */
/*   Updated: 2023/02/01 19:00:33 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = (ft_strlen(s1) - 1);
	while (j > 0 && ft_strchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j + 1 - i));
}
