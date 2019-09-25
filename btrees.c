/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btrees.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:52:53 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 21:29:28 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_btree	*node_stat_parser(struct stat *fdata, t_defs stuff, t_format *max)
{
	struct group		*group;
	struct passwd		*user;
	t_btree				*node;

	node = (t_btree *)malloc(sizeof(t_btree));
	node->right = NULL;
	node->left = NULL;
	user = getpwuid(fdata->st_uid);
	group = getgrgid(fdata->st_gid);
	node->rights = write_mods_rights(fdata->st_mode);
	node->n_links = fdata->st_nlink;
	node->owner = ft_strdup(user->pw_name);
	node->group = ft_strdup(group->gr_name);
	node->size = fdata->st_size;
	node->last_mod = (stuff.date);
	node->n_sec = fdata->st_mtimespec.tv_sec;
	node->size = fdata->st_size;
	node->name = stuff.name;
	node->block = fdata->st_blocks;
	max->links += fdata->st_blocks;
	format_track(node, max);
	return (node);
}

t_flist	*add_flst(char *name, t_flist *head, char *args)
{
	t_flist *new;

	if (head == NULL)
	{
		new = (t_flist *)malloc(sizeof(t_flist));
		new->args = args;
		new->left = NULL;
		new->right = NULL;
		new->name = name;
		head = new;
		return (head);
	}
	if (ft_a_strcmp(name, head->name) <= 0)
		head->left = add_flst(name, head->left, args);
	else
		head->right = add_flst(name, head->right, args);
	return (head);
}

t_btree	*binsert(t_btree *spot, struct stat *fdata, t_defs stuff, t_format *max)
{
	int		alpha;
	long	cmp;

	if (spot == NULL)
		return (node_stat_parser(fdata, stuff, max));
	alpha = ft_a_strcmp(stuff.name, spot->name);
	cmp = stuff.current_time - spot->n_sec;
	if ((alpha <= 0 && ft_strchr(stuff.args, 't') == NULL) ||
	(ft_strchr(stuff.args, 't') && cmp >= 0))
	{
		spot->left = binsert(spot->left, fdata, stuff, max);
	}
	else
	{
		spot->right = binsert(spot->right, fdata, stuff, max);
	}
	return (spot);
}

void	free_btree(t_btree *head)
{
	if (head == NULL)
		return ;
	else
	{
		free(head->name);
		free(head->rights);
		free(head->group);
		free(head->last_mod);
		free(head->owner);
		free_btree(head->left);
		free_btree(head->right);
		free(head);
	}
}

void	free_bftree(t_flist *head)
{
	if (head == NULL)
		return ;
	else
	{
		free(head->name);
		free_bftree(head->left);
		free_bftree(head->right);
		free(head);
	}
}
