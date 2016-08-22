/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 02:52:37 by dmathe            #+#    #+#             */
/*   Updated: 2016/08/21 02:52:40 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*make_path(char *s1, char *s2, char *s3)
{
	s1 = (char *)malloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s3) + 2));
	ft_strcpy(s1, s2);
	ft_strcat(s1, "/");
	ft_strcat(s1, s3);
	return (s1);
}

void				display_l_fold(char *param, t_opt *opt)
{
	t_list			*tmp;
	t_list			*list;
	t_list			*rmajfold;
	char			*str;
	int				i;

	i = 0;
	rmajfold = NULL;
	list = NULL;
	list = ft_ls(param, list, opt);
	check_total(param, list, opt);
	tmp = list;
	if (!list)
		return ;
	while (list)
	{
		str = make_path(str, param, list->data);
		if (fold_l(str, param, list, opt))
			list_add_next(&rmajfold, link_init(str));
		list = list->next;
	}
	print_l(tmp, opt);
	if (rmajfold)
		recurs(rmajfold, opt);
}

void				display_l_file(t_list *file, t_opt *opt)
{
	struct stat		buf;
	t_list			*tmp;

	tmp = NULL;
	tmp = sort_opt(file, opt);
	while (tmp)
	{
		stat(tmp->data, &buf);
		display_fold(tmp->data, opt);
		ft_putstr(tmp->data);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}
