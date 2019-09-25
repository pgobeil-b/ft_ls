/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:29:07 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 21:35:47 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		print_total(int links)
{
	char	*tmp;
	char	*num;

	num = ft_itoa(links);
	tmp = ft_strjoin("total ", num);
	ft_putendl(tmp);
	free(num);
	free(tmp);
}

void		wrap_up(t_defs i, t_format max, t_btree *head, t_flist *head_f)
{
	if (ft_strchr(i.args, 'l') && max.links != 0)
		print_total(max.links);
	print_tree(head, &max, i);
	free_btree(head);
	if (ft_strchr(i.args, 'R') != NULL)
	{
		print_every_folder(head_f, i);
		free_bftree(head_f);
	}
}

void		print_folder(char *path, t_defs i)
{
	t_normer		n;

	if (ft_strchr(i.args, 'R'))
		ft_putchar('\n');
	n = init_normer(path, i);
	if (ft_strcmp(".", path) != 0)
		ft_putendl(path);
	while (n.fold != NULL && (n.cnt = readdir(n.fold)))
	{
		lstat(n.path = do_path(path, n.cnt->d_name), &n.stats);
		i.name = ft_strdup(n.cnt->d_name);
		i.date = ft_strdup(ctime(&n.stats.st_mtimespec.tv_sec));
		i.current_time = n.stats.st_mtimespec.tv_sec;
		if (RECURSION_CONDITION)
			n.head_f = add_flst(do_path(path, n.cnt->d_name), n.head_f, i.args);
		if (!(n.head) && (n.cnt->d_name[0] != '.' || ft_strchr(i.args, 'a')))
			n.head = node_stat_parser(&n.stats, i, &n.max);
		else if (n.cnt->d_name[0] != '.' || ft_strchr(i.args, 'a'))
			binsert(n.head, &n.stats, i, &n.max);
		free(n.path);
	}
	n.fold ? closedir(n.fold) : ft_putendl("permission denied");
	wrap_up(i, n.max, n.head, n.head_f);
}

void		print_every_folder(t_flist *head, t_defs info)
{
	if (head != NULL)
	{
		print_every_folder(head->left, info);
		print_folder(head->name, info);
		print_every_folder(head->right, info);
	}
}

void		print_tree(t_btree *head, t_format *max, t_defs info)
{
	char *tmp;

	tmp = NULL;
	if (head != NULL)
	{
		if (ft_strchr(info.args, 'r'))
			print_tree(head->right, max, info);
		else
			print_tree(head->left, max, info);
		if (ft_strchr(info.args, 'l'))
			ft_putendl(tmp = (long_format(head, max)));
		else
		{
			ft_putendl(head->name);
		}
		if (ft_strchr(info.args, 'r'))
			print_tree(head->left, max, info);
		else
			print_tree(head->right, max, info);
		if (tmp)
			free(tmp);
	}
}
