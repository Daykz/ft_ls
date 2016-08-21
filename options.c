/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 00:31:17 by dmathe            #+#    #+#             */
/*   Updated: 2016/05/24 17:08:45 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*fmt(char *time)
{
	int i;

	i = ft_strlen(time);
	time[i - 9] = '\0';
	return (time + 4);
}

char	*w_perms(mode_t mode)
{
	char *mod;

	mod = ft_strnew(10);
	mod[0] = ((mode & S_IRUSR) ? 'r' : '-');
	mod[1] = ((mode & S_IWUSR) ? 'w' : '-');
	mod[2] = ((mode & S_IXUSR) ? 'x' : '-');
	mod[3] = ((mode & S_IRGRP) ? 'r' : '-');
	mod[4] = ((mode & S_IWGRP) ? 'w' : '-');
	mod[5] = ((mode & S_IXGRP) ? 'x' : '-');
	mod[6] = ((mode & S_IROTH) ? 'r' : '-');
	mod[7] = ((mode & S_IWOTH) ? 'w' : '-');
	mod[8] = ((mode & S_IXOTH) ? 'x' : '-');
	mod[9] = '\0';
	return (mod);
}

char		w_type(mode_t type)
{
	char c;

	if (type == 8630)
		c = 'c';
	if (S_ISLNK(type))
		c = 'l';
	if (S_ISBLK(type))
		c = 'b';
	if (S_ISDIR(type))
		c = 'd';
	if (S_ISREG(type))
		c = '-';
	if (S_ISSOCK(type))
		c = 's';
	return (c);
}

void		init_file(t_file *file)
{
	file->link = 0;
	file->size = 0;
	file->timet = 0;
}

void		display_fold(char *param, t_opt *opt)
{
	t_file	*fold;
	struct stat	buf;
	int 	i;

	i = 8;
	fold = (t_file *)malloc(sizeof(t_file));
	if (fold == NULL)
		exit (1);
	(void)opt;
	init_file(fold);
	stat(param, &buf);
	fold->type = w_type(buf.st_mode);
	fold->perms = w_perms(buf.st_mode);
	fold->link = buf.st_nlink;
	fold->uid = ft_strdup(getpwuid(buf.st_uid)->pw_name);
	fold->gid = ft_strdup(getgrgid(buf.st_gid)->gr_name);
	fold->size = buf.st_size;
	fold->times = fmt(ctime(&buf.st_mtime));
	disp_fold(fold);
}

void		display_l_file(t_list *file, t_opt *opt)
{
	struct stat	buf;
	t_list *tmp;

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

void		display_l_fold(char *param, t_opt *opt)
{
	t_list	*tmp;
	t_list	*list;
	t_list	*rmajfold;
	char	*str;
	int 	i;

	i = 0;
	rmajfold = NULL;
	list = NULL;
	list = ft_ls(param, list, opt);
	check_total(param, list, opt);
	tmp = list;
	if (!list)
		return;
	while (list)
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(param) + ft_strlen((char *)list->data) + 2));
		ft_strcpy(str, param);
		ft_strcat(str, "/");
		ft_strcat(str, (char *)list->data);
		if (str[ft_strlen(param) + 1] != '.' || (str[ft_strlen(param) + 1] == '.' && opt->a == 1))
		{
			if (opt->rmaj && check_rmaj(str, opt))
			{
				if (ft_strcmp(list->data, ".") && ft_strcmp(list->data, ".."))
					list_add_next(&rmajfold, link_init(str));
			}
			if (opt->l)
			{
				display_fold(str, opt);
				ft_putstr((char *)list->data);
				ft_putstr("\n");
			}
		}
		list = list->next;
	}
	if (!opt->l)
	{
		if (opt->a)
			print_list(tmp);
		else
			print_list_without_point(tmp);
	}
	if (rmajfold)
	{
		ft_putstr("\n");
		opt->if_rmaj++;
		begin_disp(rmajfold, opt);
		opt->if_rmaj--;
	}
}
