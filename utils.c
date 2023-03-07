/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:17:56 by alvina            #+#    #+#             */
/*   Updated: 2023/03/07 11:12:42 by alvina           ###   ########.fr       */
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
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
    if (nptr[i])
        return (0);
    else
	    return (nb * neg);
}

t_list	*ft_list_at(t_list *begin_list, int nbr)
{
	int	i;
	t_list			*element;

	i = 0;
	element = begin_list;
	while (i != nbr && (element))
	{
		element = element->next;
		i++;
	}
	if (i == nbr)
		return (element);
	else
		return (0);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = NULL;
	list = malloc(sizeof(t_list));
	if (list)
	{
		list->philo = content;
		list->next = NULL;
	}
	return (list);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		if (lst && new)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
    return (*lst);
}