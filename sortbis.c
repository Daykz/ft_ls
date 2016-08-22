/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortbis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 00:31:56 by dmathe            #+#    #+#             */
/*   Updated: 2016/08/22 00:31:58 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*sort_opt(t_list *file, t_opt *opt)
{
	if (opt->t == 1)
	{
		sort_files(file);
		sort_times_file(file);
	}
	else
		sort_files(file);
	if (opt->r == 1)
		reverse_sort_files(file);
	return (file);
}

void		reverse_sort_files(t_list *list)
{
	t_list	*tmp;
	int		n;
	int		i;

	tmp = list;
	n = (int)list_size(tmp);
	while (n >= 0)
	{
		i = 1;
		while (i < n && tmp->next)
		{
			list_swap_data(tmp, tmp->next);
			tmp = tmp->next;
			i++;
		}
		n--;
		tmp = list;
	}
}

void		sort_files(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp((char *)tmp->data, (char *)tmp->next->data) > 0)
			{
				list_swap_data(tmp, tmp->next);
				tmp = list;
			}
			else
				tmp = tmp->next;
		}
	}
}
