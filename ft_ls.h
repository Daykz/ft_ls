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
}					t_opt;

void	sort_files(t_list *list);
void	print_list(t_list *list);

#endif
