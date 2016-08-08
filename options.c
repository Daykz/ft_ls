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

	i = 0;
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
	printf("%c%s  %d %s  %s", fold->type, fold->perms, fold->link, fold->uid, fold->gid);
	printf("%8d %s ", fold->size, fold->times);
}

void		display_file(char *param, t_opt *opt)
{
	t_file	*file;
	struct stat	buf;
	int 	i;

	i = 0;
	file = (t_file *)malloc(sizeof(t_file));
	if (file == NULL)
		exit (1);
	(void)opt;
	init_file(file);
	stat(param, &buf);
	file->type = w_type(buf.st_mode);
	file->perms = w_perms(buf.st_mode);
	file->link = buf.st_nlink;
	file->uid = ft_strdup(getpwuid(buf.st_uid)->pw_name);
	file->gid = ft_strdup(getgrgid(buf.st_gid)->gr_name);
	file->size = buf.st_size;
	file->times = fmt(ctime(&buf.st_mtime));
	printf("%c%s  %d %s  %s", file->type, file->perms, file->link, file->uid, file->gid);
	printf("%8d %s ", file->size, file->times);
	printf("%s\n", param);
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
		display_file(tmp->data, opt);
		tmp = tmp->next;
	}
}

void		display_l_fold(char *param, t_opt *opt)
{
	t_list	*tmp;
	t_list	*list;
	char	*str;
	struct stat	buf;

	list = NULL;
	list = ft_ls(param, list, opt);
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
			stat(str, &buf);
			if (opt->l)
			{
				display_fold(str, opt);
				printf("%s\n", (char *)list->data);
			}
		}
		list = list->next;
	}
	if (!opt->l)
		print_list(tmp);
}

void		ls_folder(char **param, t_opt *opt, int i)
{
	while (param[i])
	{
		opt->file = 0;
		opt->repert = 0;
		if (check_valid(param[i], opt) == -1)
			printf("ls: %s: No such file or directory\n", param[i]);
		if (opt->repert == 1)
		{
			display_l_fold(param[i], opt);
		}
		i++;
	}
}

void		ls_files(char **param, t_opt *opt, int i)
{
	int 	j;
	t_list	*file;

	j = 0;
	file = NULL;
	if (!param[i])
		return;
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
	if (opt->l == 1)
		display_l_file(file, opt);
	else
	{
		display(file, opt);
		print_list(file);
	}
}
