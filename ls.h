/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:59:12 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 21:35:21 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include "libft/includes/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

# define F_ARG(m) ft_strchr(i.args, m)
# define D_CHK S_ISDIR(n.stats.st_mode) != 0
# define C_CHK(m) ft_strcmp(m, n.cnt->d_name) != 0
# define A_CND (n.cnt->d_name[0] != '.' || F_ARG('a'))) && C_CHK("..") != 0
# define RECURSION_CONDITION (D_CHK && C_CHK(".") && A_CND && F_ARG('R')

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			*rights;
	int				n_links;
	char			*owner;
	char			*group;
	int				size;
	char			*last_mod;
	char			*name;
	int				block;
	long			n_sec;
}					t_btree;

typedef struct		s_defs
{
	char			*args;
	char			*name;
	char			*date;
	char			**targets;
	int				n_targ;
	long			current_time;
}					t_defs;

typedef struct		s_format
{
	int				links;
	int				top_l;
	int				top_o;
	int				top_g;
	int				top_s;
}					t_format;

typedef struct		s_flist
{
	struct s_flist	*left;
	struct s_flist	*right;
	char			*name;
	char			*args;
}					t_flist;

typedef struct		s_normer
{
	t_btree			*head;
	t_flist			*head_f;
	t_defs			info;
	struct stat		stats;
	DIR				*fold;
	struct dirent	*cnt;
	t_format		max;
	int				i;
	char			*path;
}					t_normer;

t_normer			file_parse(t_normer n, char **argv);
char				*write_mods_rights(mode_t mods);
t_flist				*add_flst(char *name, t_flist *head, char *args);
t_btree				*binsert(t_btree *spot, struct stat *fdata, t_defs stuff,
					t_format *max);
void				print_tree(t_btree *head, t_format *max, t_defs info);
void				print_folder(char *path, t_defs info);
void				print_every_folder(t_flist *head, t_defs info);
void				free_bftree(t_flist *head);
char				*long_format(t_btree *node, t_format *max);
char				*do_path(char *current, char *obj_name);
t_format			init_max(void);
t_normer			file_parse(t_normer n, char **argv);
t_normer			init_normer(char *path, t_defs info);
t_btree				*node_stat_parser(struct stat *fdata, t_defs stuff,
					t_format *max);
t_flist				*add_flst(char *name, t_flist *head, char *args);
void				free_btree(t_btree *head);
void				format_track(t_btree *node, t_format *max);

#endif
