/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:30:01 by apanikov          #+#    #+#             */
/*   Updated: 2023/01/24 19:33:48 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*new;
	int		j;

	j = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!new)
	{
		return (0);
	}
	while (s1[j])
	{
		new[j] = s1[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}
