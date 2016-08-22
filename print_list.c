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

void	print_l(t_list *list, t_opt *opt)
{
	if (!opt->l)
	{
		if (opt->a)
			print_list(list);
		else
			print_list_without_point(list);
	}
}

int		check_rmaj(char *str, t_opt *opt)
{
	opt->file = 0;
	opt->repert = 0;
	check_valid(str, opt);
	if (opt->repert)
		return (1);
	else
		return (0);
}

void	print_list_without_point(t_list *list)
{
	if (list)
	{
		while (list)
		{
			if (((char *)list->data)[0] != '.')
			{
				ft_putstr((char *)list->data);
				if (list->next)
					ft_putstr("  ");
			}
			list = list->next;
		}
		ft_putchar('\n');
	}
}

void	print_list(t_list *list)
{
	if (list)
	{
		while (list)
		{
			ft_putstr((char *)list->data);
			if (list->next)
				ft_putstr("  ");
			list = list->next;
		}
		ft_putchar('\n');
	}
}

void	begin_disp(t_list *fold, t_opt *opt)
{
	int	i;

	i = 0;
	fold = sort_opt(fold, opt);
	while (fold)
	{
		if (opt->if_error || opt->if_file || opt->if_fold != 1 || opt->if_rmaj)
		{
			if (!opt->if_file && !i)
				i++;
			else
				ft_putstr("\n");
			ft_putstr(fold->data);
			ft_putchar(':');
			if (check_if_empty(fold->data, opt) || !opt->l)
			{
				ft_putstr("\n");
			}
		}
		display_l_fold(fold->data, opt);
		fold = fold->next;
	}
}
