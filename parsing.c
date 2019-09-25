/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:12:45 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 21:57:23 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char		*write_mods_rights(mode_t mods)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 11);
	str[0] = S_ISDIR(mods) ? 'd' : '-';
	if (S_ISLNK(mods))
		str[0] = 'l';
	if (S_ISBLK(mods))
		str[0] = 'b';
	if (S_ISCHR(mods))
		str[0] = 'c';
	if (S_ISFIFO(mods))
		str[0] = 'p';
	if (S_ISSOCK(mods))
		str[0] = 's';
	str[1] = mods & S_IRUSR ? 'r' : '-';
	str[2] = mods & S_IWUSR ? 'w' : '-';
	str[3] = mods & S_IXUSR ? 'x' : '-';
	str[4] = mods & S_IRGRP ? 'r' : '-';
	str[5] = mods & S_IWGRP ? 'w' : '-';
	str[6] = mods & S_IXGRP ? 'x' : '-';
	str[7] = mods & S_IROTH ? 'r' : '-';
	str[8] = mods & S_IWOTH ? 'w' : '-';
	str[9] = mods & S_IXOTH ? 'x' : '-';
	str[10] = '\0';
	return (str);
}

t_defs		targ_split(int argc, char **argv, t_defs info)
{
	int		k;
	int		i;

	i = 1;
	k = 0;
	info.targets = (char **)malloc(sizeof(char *) * info.n_targ + 1);
	while (i > argc)
	{
		if (argv[i][0] != '-')
		{
			info.targets[k] = (argv[i]);
			k++;
		}
		i++;
	}
	return (info);
}

t_defs		arg_str(int argc, char **argv)
{
	int			i;
	int			j;
	t_defs		info;

	i = 0;
	j = -1;
	info.args = (char *)malloc(sizeof(char) * 6);
	ft_putc_in_str(info.args, '_', 5, 0);
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			info.n_targ++;
		if (ft_strchr(argv[i], 'a') != NULL && argv[i][0] == '-')
			info.args[0] = 'a';
		if (ft_strchr(argv[i], 'l') != NULL && argv[i][0] == '-')
			info.args[1] = 'l';
		if (ft_strchr(argv[i], 'R') != NULL && argv[i][0] == '-')
			info.args[2] = 'R';
		if (ft_strchr(argv[i], 'r') != NULL && argv[i][0] == '-')
			info.args[3] = 'r';
		if (ft_strchr(argv[i], 't') != NULL && argv[i][0] == '-')
			info.args[4] = 't';
	}
	info.args[5] = '\0';
	return (info);
}

int			check_args(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	while (++i < argc)
	{
		j = 1;
		if (argv[i][0] == '-')
		{
			while (argv[i][j] != '\0' && (argv[i][j] == 'R' ||
			argv[i][j] == 'r' || argv[i][j] == 'l'
			|| argv[i][j] == 't' || argv[i][j] == 'a'))
				j++;
			if (argv[i][j] != '\0' || j == 1)
				return (1);
		}
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_normer		n;
	int				stat_ret;

	n.i = 0;
	n.info = arg_str(argc, argv);
	n.max = init_max();
	if (check_args(argc, argv) == 1)
		return (err_ret("ls: illegal option\nusage: ls [-alrRt] [file]"));
	while (++n.i < argc && n.info.n_targ > 0)
		if (argv[n.i][0] != '-')
		{
			if ((stat_ret = lstat(argv[n.i], &n.stats)) == -1)
			{
				ft_putstr(argv[n.i]);
				ft_putendl((": no such file or directory"));
			}
			if (S_ISDIR(n.stats.st_mode) != 0 && stat_ret != -1)
				print_folder(argv[n.i], n.info);
			if (S_ISDIR(n.stats.st_mode) == 0 && stat_ret != -1)
				file_parse(n, argv);
		}
	if (n.info.n_targ == 0)
		print_folder(".", n.info);
	free(n.info.args);
	return (0);
}
