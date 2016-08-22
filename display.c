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

int					check_if_empty(char *str, t_opt *opt)
{
	DIR				*dir;
	struct dirent	*ret;
	t_list			*empty;
	char			*tmp;

	(void)opt;
	empty = NULL;
	dir = opendir(str);
	while ((ret = readdir(dir)))
		list_add_next(&empty, link_init((void *)ret->d_name));
	closedir(dir);
	while (empty)
	{
		tmp = empty->data;
		if (tmp[0] != '.' || (tmp[0] == '.' && opt->a))
			return (0);
		empty = empty->next;
	}
	return (1);
}

void				ls_error(char **param, t_opt *opt, int i)
{
	t_list			*error;

	error = NULL;
	while (param[i])
	{
		if (check_valid(param[i], opt) == -1)
		{
			list_add_next(&error, link_init(param[i]));
			opt->if_error = 1;
		}
		i++;
	}
	error = sort_opt(error, opt);
	while (error)
	{
		opt->if_error++;
		ft_putstr("ls: ");
		ft_putstr(error->data);
		ft_putstr(": No such file or directory");
		ft_putchar('\n');
		error = error->next;
	}
}

void				check_total(char *param, t_list *list, t_opt *opt)
{
	struct stat		buf;
	int				total;
	char			*str;
	int				size;
	char			*tmp;

	total = 0;
	while (list)
	{
		tmp = NULL;
		str = list->data;
		tmp = (char *)malloc(sizeof(char) * \
			(ft_strlen(param) + ft_strlen((char *)list->data) + 2));
		ft_strcpy(tmp, param);
		ft_strcat(tmp, "/");
		ft_strcat(tmp, list->data);
		if (str[0] != '.' || (str[0] == '.' && opt->a == 1))
		{
			stat(tmp, &buf);
			size = buf.st_size;
			total += count_total(buf.st_size);
		}
		list = list->next;
	}
	total2(param, total, opt);
}

int					count_total(int len)
{
	int				size;
	int				n;

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

void				display(t_list *file, t_opt *opt)
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
