/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 23:18:01 by dmathe            #+#    #+#             */
/*   Updated: 2016/08/08 23:18:03 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_error(char **param, t_opt *opt, int i)
{
	while (param[i])
	{
		if (check_valid(param[i], opt) == -1)
		{
			printf("ls: %s: No such file or directory\n", param[i]);
			opt->if_error = 1;
		}
		i++;
	}
}

void	check_total(t_list *list, t_opt *opt)
{
	struct stat buf;
	static int 	total = 0;
	char 		*str;

	(void)opt;
	while (list)
	{
		str = list->data;
		if (str[0] != '.' || (str[0] == '.' && opt->a == 1))
		{
			stat((char *)list->data, &buf);
			total += count_total(buf.st_size);
		}
		list = list->next;
	}
	if (opt->l)
		printf("total %d\n", total);
}

int		count_total(int	len)
{
	int	size;
	int	n;

	n = 0;
	size = 512;
	if (!len)
		return (0);
	while (len > size)
	{
		len -= size;
		n++;
	}
	return (n + 1);
}

void	display(t_list *file, t_opt *opt)
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
}