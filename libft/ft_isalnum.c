/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:11:04 by apanikov          #+#    #+#             */
/*   Updated: 2023/01/24 18:20:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	a;

	a = ft_isalpha(c);
	if (a == 1)
		return (1);
	else
		a = ft_isdigit(c);
	if (a == 1)
		return (1);
	else
		return (0);
}
