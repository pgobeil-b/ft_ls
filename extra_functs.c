/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:31:35 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 21:02:30 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_normer	file_parse(t_normer n, char **argv)
{
	n.info.name = argv[n.i];
	n.info.date = ctime(&n.stats.st_mtimespec.tv_sec);
	n.head = node_stat_parser(&n.stats, n.info, &n.max);
	format_track(n.head, &n.max);
	ft_strchr(n.info.args, 'l') ?
	ft_putendl(long_format(n.head, &n.max)) : ft_putendl(argv[n.i]);
	return (n);
}
