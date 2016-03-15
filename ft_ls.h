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
	int 			repert;
}					t_opt;

typedef	struct 		s_file
{
	char 			type;
	char 			*gid;
	char 			*uid;
	int 			link;
	char 			*perms;
	int 			size;
	char 			*times;

}					t_file;

void	sort_files(t_list *list);
void	reverse_sort_files(t_list *list);
void	print_list(t_list *list);
void	print_list_without_point(t_list *list);
void	init_opt(t_opt *opt);
void	check_opt(char *param, t_opt *opt);
int 	check_param(char **param, t_opt *opt);
void		dispatch(char **param, t_opt *opt);
int 		check_valid(char *param, t_opt *opt);
void		ls_files(char **param, t_opt *opt);
void		ls_folder(char **param, t_opt *op);
t_list		*ft_ls(char *str, t_list *list, t_opt *opt);
void	sort_times(t_list *list, char *str);

#endif
