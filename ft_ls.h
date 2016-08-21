#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <sys/dirent.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct		s_opt
{
	int				a;
	int				r;
	int				rmaj;
	int				t;
	int				l;
	int 			file;
	int 			if_file;
	int 			if_fold;
	int 			if_error;
	int 			repert;
	int 			if_rmaj;
}					t_opt;

typedef	struct 		s_file
{
	char 			type;
	char 			*gid;
	char 			*uid;
	int 			link;
	char 			*perms;
	int 			size;
	int 			total;
	long int		timet;
	char 			*times;

}					t_file;

void		display_l_file(t_list *file, t_opt *opt);
void		disp_fold(t_file *fold);
void		total2(char *param, int total, t_opt *opt);
void	print_l(t_list *list, t_opt *opt);
int		check_rmaj(char *str, t_opt *opt);
void		begin_disp(t_list *fold, t_opt *opt);
int 	check_if_empty(char *str, t_opt *opt);
void	ls_error(char **param, t_opt *opt, int i);
void		init_file(t_file *file);
void	check_total(char *param, t_list *list, t_opt *opt);
int		count_total(int	len);
void		display_l_fold(char *param, t_opt *opt);
void	display(t_list *file, t_opt *opt);
void	sort_files(t_list *list);
void	reverse_sort_files(t_list *list);
void	print_list(t_list *list);
void	print_list_without_point(t_list *list);
void	init_opt(t_opt *opt);
void	check_opt(char *param, t_opt *opt);
int 	check_param(char **param, t_opt *opt);
void		dispatch(char **param, t_opt *opt);
int 		check_valid(char *param, t_opt *opt);
void		ls_files(char **param, t_opt *opt, int i);
void		ls_folder(char **param, t_opt *op, int i);
t_list		*ft_ls(char *str, t_list *list, t_opt *opt);
void	sort_times(t_list *list, char *str);
void	reverse_sort_files(t_list *list);
void	sort_times_file(t_list *list);
t_list	*sort_opt(t_list *file, t_opt *opt);

#endif
