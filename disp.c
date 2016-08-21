/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 02:08:19 by dmathe            #+#    #+#             */
/*   Updated: 2016/08/21 02:08:21 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		disp_fold(t_file *fold)
{
	int 	i;

	i = 8;
	ft_putchar(fold->type);
	ft_putstr(fold->perms);
	ft_putstr("  ");
	ft_putnbr(fold->link);
	ft_putchar(' ');
	ft_putstr(fold->uid);
	ft_putstr("  ");
	ft_putstr(fold->gid);
	while (i > (int)ft_strlen(ft_itoa(fold->size)))
	{
		ft_putchar(' ');
		i--;	
	}
	ft_putnbr(fold->size);
	ft_putchar(' ');
	ft_putstr(fold->times);
	ft_putchar(' ');
}

void		total2(char *param, int total, t_opt *opt)
{
	if (opt->l && !check_if_empty(param, opt))
	{
		if (opt->if_rmaj || opt->if_fold > 1 || (opt->if_fold == 1 \
			&& (opt->if_error || opt->if_file)))
			ft_putchar('\n');
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
}

void		ls_folder(char **param, t_opt *opt, int i)
{
	t_list	*fold;

	fold = NULL;
	while (param[i])
	{
		opt->file = 0;
		opt->repert = 0;
		check_valid(param[i], opt);
		if (opt->repert == 1)
		{
			opt->if_fold++;
			list_add_next(&fold, link_init(param[i]));
		}
		i++;
	}
	begin_disp(fold, opt);
}

void		ls_l_files(t_list *file, t_opt *opt)
{
	if (opt->l == 1)
		display_l_file(file, opt);
	else
	{
		display(file, opt);
		print_list(file);
	}
}

void		ls_files(char **param, t_opt *opt, int i)
{
	int		j;
	t_list	*file;

	j = 0;
	file = NULL;
	if (!param[i])
		return ;
	while (param[i])
	{
		opt->file = 0;
		opt->repert = 0;
		check_valid(param[i], opt);
		if (opt->file == 1)
		{
			opt->if_file = 1;
			list_add_next(&file, link_init(param[i]));
		}
		j++;
		i++;
	}
	ls_l_files(file, opt);
}
