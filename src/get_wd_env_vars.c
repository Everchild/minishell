/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wd_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 16:02:19 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/04 16:27:20 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void				get_underscore_var(t_dblist **save, char *exe)
{
	t_node			*node;
	char			*tmp;
	char			*tmp2;
	char			shpath[BUFF_SIZE];

	node = NULL;
	tmp = NULL;
	ft_bzero(shpath, BUFF_SIZE);
	if (getcwd(shpath, BUFF_SIZE))
	{
		tmp = ft_strjoin("_=", shpath);
		tmp2 = ft_strcjoin(tmp, exe, '/');
		node = create_node(tmp2, ft_strlen(tmp2) + 1);
		if (node)
			add_node_end(save, node);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
}

void				get_pwd_var(t_dblist **save)
{
	t_node			*node;
	char			*tmp;
	char			shpath[BUFF_SIZE];

	node = NULL;
	tmp = NULL;
	ft_bzero(shpath, BUFF_SIZE);
	if (getcwd(shpath, BUFF_SIZE))
	{
		tmp = ft_strjoin("PWD=", shpath);
		node = create_node(tmp, ft_strlen(tmp) + 1);
		if (node)
			add_node_end(save, node);
		ft_strdel(&tmp);
	}
}
