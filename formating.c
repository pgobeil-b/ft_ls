/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:31:44 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 21:17:20 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_format	init_max(void)
{
	t_format max;

	max.links = 0;
	max.top_g = 0;
	max.top_l = 0;
	max.top_o = 0;
	max.top_s = 0;
	return (max);
}

void		format_track(t_btree *node, t_format *max)
{
	if (ft_digit(node->n_links) > max->top_l)
		max->top_l = ft_digit(node->n_links);
	if ((int)ft_strlen(node->owner) > max->top_o)
		max->top_o = ft_strlen(node->owner);
	if (ft_digit(node->size) > max->top_s)
		max->top_s = ft_digit(node->size);
	if ((int)ft_strlen(node->group) > max->top_g)
		max->top_g = ft_strlen(node->group);
}

char		*long_format(t_btree *node, t_format *max)
{
	int				t_len;
	unsigned int	i;
	char			*res;

	i = 0;
	t_len = ft_strlen(node->name) + ft_strlen(node->rights) + max->top_g +
	max->top_s + max->top_o + max->top_l + ft_strlen(node->last_mod) + 9;
	res = (char *)malloc(sizeof(char) * t_len);
	ft_bzero(res, t_len - 1);
	i = ft_strsubcpy(node->rights, res, ft_strlen(node->rights), i);
	i = ft_putc_in_str(res, ' ', 2 + max->top_l - ft_digit(node->n_links), i);
	i = ft_strdmpnfree(ft_itoa(node->n_links), res, ft_digit(node->n_links), i);
	i = ft_putc_in_str(res, ' ', 1 + max->top_o - ft_strlen(node->owner), i);
	i = ft_strsubcpy(node->owner, res, ft_strlen(node->owner), i);
	i = ft_putc_in_str(res, ' ', 2 + max->top_g - ft_strlen(node->group), i);
	i = ft_strsubcpy(node->group, res, ft_strlen(node->group), i);
	i = ft_putc_in_str(res, ' ', 2 + max->top_s - ft_digit(node->size), i);
	i = ft_strdmpnfree(ft_itoa(node->size), res, ft_digit(node->size), i);
	i = ft_putc_in_str(res, ' ', 1, i);
	i = ft_strsubcpy(node->last_mod + 4, res, ft_strlen(node->last_mod) - 4, i);
	i = ft_putc_in_str(res, ' ', 1, i - 9);
	i = ft_strsubcpy(node->name, res, ft_strlen(node->name), i);
	res[i] = '\0';
	return (res);
}

char		*do_path(char *current, char *obj_name)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) *
	(ft_strlen(obj_name) + ft_strlen(current) + 2));
	while (current[i] != '\0')
	{
		res[i] = current[i];
		i++;
	}
	res[i] = '/';
	i++;
	while (obj_name[j] != '\0')
	{
		res[i] = obj_name[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

t_normer	init_normer(char *path, t_defs info)
{
	t_normer norm;

	norm.head = NULL;
	norm.head_f = NULL;
	norm.info = info;
	norm.max = init_max();
	norm.fold = opendir(path);
	return (norm);
}
