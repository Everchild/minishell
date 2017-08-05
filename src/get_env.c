/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 15:57:16 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/04 16:27:17 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void			increment_shlvl(t_node *shlvl)
{
	char			*tmp;
	size_t			lvl;

	tmp = ft_strchr(shlvl->content, '=') + 1;
	lvl = ft_atoi(tmp);
	lvl++;
	tmp = ft_itoa(lvl);
	ft_memdel(&(shlvl->content));
	shlvl->content = ft_strjoinf("SHLVL=", tmp, 2);
}

static void			handle_shlvl(t_dblist **save)
{
	size_t			i;
	t_node			*cur;

	i = 0;
	cur = (*save)->start;
	while (i < (*save)->nb_nodes)
	{
		if (!ft_strncmp("SHLVL=", cur->content, 6))
			break ;
		cur = cur->next;
		i++;
	}
	if (i == (*save)->nb_nodes)
	{
		cur = create_node("SHLVL=1", 8);
		if (cur)
			add_node_end(save, cur);
	}
	else
		increment_shlvl(cur);
}

static void			check_env_vars(t_dblist **save, char *exe)
{
	size_t			i;
	t_node			*cur;

	i = 0;
	cur = (*save)->start;
	while (i < (*save)->nb_nodes)
	{
		if (!ft_strncmp("PWD=", cur->content, 4))
			break ;
		cur = cur->next;
		i++;
	}
	if (i == (*save)->nb_nodes)
		get_pwd_var(save);
	i = 0;
	cur = (*save)->start;
	while (i < (*save)->nb_nodes)
	{
		if (!ft_strncmp("_=", cur->content, 2))
			break ;
		cur = cur->next;
		i++;
	}
	if (i == (*save)->nb_nodes)
		get_underscore_var(save, exe);
}

static void			handle_null_env(t_dblist **save, char *exe)
{
	t_node			*node;

	node = NULL;
	if (!*save)
		*save = create_list();
	if (*save)
	{
		get_pwd_var(save);
		get_underscore_var(save, exe);
		node = create_node("SHLVL=1", 8);
		if (node)
			add_node_end(save, node);
	}
}

void			get_env(t_dblist **save, char **orig, char *exe)
{
	t_node			*node;

	node = NULL;
	if (orig && *orig)
	{
		if (!*save)
			*save = create_list();
		if (*save)
		{
			while (*orig)
			{
				node = create_node(*orig, ft_strlen(*orig) + 1);
				if (node)
					add_node_end(save, node);
				orig++;
			}
			check_env_vars(save, exe);
			handle_shlvl(save);
		}
	}
	else
		handle_null_env(save, exe);
}
