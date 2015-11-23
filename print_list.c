/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:03:36 by dmathe            #+#    #+#             */
/*   Updated: 2015/11/23 15:03:38 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_without_point(t_list *list)
{
	if (list)
	{
		while (list)
		{
			if (((char *)list->data)[0] != '.')
			{
				ft_putstr((char *)list->data);
				ft_putchar(' ');
			}
			list = list->next;
		}
	}
}

void	print_list(t_list *list)
{
	if (list)
	{
		while (list)
		{
			ft_putstr((char *)list->data);
			ft_putchar(' ');
			list = list->next;
		}
	}
}
