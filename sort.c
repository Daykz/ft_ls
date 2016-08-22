/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 17:53:47 by dmathe            #+#    #+#             */
/*   Updated: 2016/05/11 17:53:49 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				file_size(t_list *list)
{
	int			i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void			sort_file(t_list *list)
{
	t_list		*tmp;
	int			i;

	i = 0;
	while (i < file_size(list))
	{
		tmp = list;
		while (tmp && tmp->next)
		{
			if (tmp->date < tmp->next->date)
				list_swap_data(tmp, tmp->next);
			else
				tmp = tmp->next;
		}
		i++;
	}
}

void			times(t_list *list)
{
	t_list		*tmp;

	tmp = list;
	while (tmp->next)
	{
		if (tmp->date < tmp->next->date)
		{
			list_swap_data(tmp, tmp->next);
			tmp = list;
		}
		else
			tmp = tmp->next;
	}
}

void			sort_times(t_list *list, char *str)
{
	t_list		*tmp;
	char		*path;
	struct stat buf;

	tmp = list;
	if (tmp)
	{
		while (tmp)
		{
			path = (char *)malloc(sizeof(char) * \
				(ft_strlen(str) + ft_strlen((char *)tmp->data) + 2));
			ft_strcpy(path, str);
			ft_strcat(path, "/");
			ft_strcat(path, (char *)tmp->data);
			stat(path, &buf);
			tmp->date = buf.st_mtime;
			tmp = tmp->next;
		}
		times(list);
	}
}

void			sort_times_file(t_list *file)
{
	t_list		*temp;
	struct stat buf;

	temp = file;
	if (temp)
	{
		while (temp)
		{
			stat(temp->data, &buf);
			temp->date = buf.st_mtime;
			temp = temp->next;
		}
		times(file);
	}
}
