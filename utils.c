/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:17:56 by alvina            #+#    #+#             */
/*   Updated: 2023/04/20 15:00:55 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
long	ft_atoll(const char *nptr)
{
	int		i;
	long    nb;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	if (!nptr || !nptr[0])
		return (-1);
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
    if (nptr[i])
        return (-1);
    else
	    return (nb * neg);
}