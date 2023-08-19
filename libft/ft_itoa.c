/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:40:01 by apanikov          #+#    #+#             */
/*   Updated: 2023/02/07 21:26:28 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_size(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_zero(char *out)
{
	out[0] = '0';
	out[1] = '\0';
	return (out);
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	char	*out;

	i = ft_size(n);
	sign = 1;
	if (n < 0)
		sign = -1;
	i = i + (n <= 0);
	out = (char *)malloc(sizeof(char) * (i + 1));
	if (!out)
		return (out);
	if (n == 0)
		return (out = ft_zero(out));
	out[i] = '\0';
	while (n != 0)
	{
		out[--i] = (char)((n % 10) * sign + '0');
		n = n / 10;
	}
	i--;
	if (sign < 0)
		out[i] = '-';
	return (out);
}
