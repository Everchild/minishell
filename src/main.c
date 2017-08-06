/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 16:08:28 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/06 12:25:10 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int					main(int argc, char **argv, char **env)
{
	t_dblist		*env_copy;
	char			*buf;
	char			*tmp;
	char			**cmd;

	if (argc == 1)
	{
		env_copy = NULL;
		buf = NULL;
		tmp = NULL;
		cmd = NULL;
		get_env(&env_copy, env, argv[0]);
		if (!env_copy)
		{
			ft_printf("unable to get env\n");
			return (0);
		}
		ft_printf("$> ");
		while (get_next_line(1, &buf))
		{
			tmp = ft_strtrimall(buf);
			cmd = ft_strsplit(tmp, ' ');
			ft_strdel(&buf);
			handle_cmd(&env_copy, cmd);
			free_tab(&cmd);
			ft_printf("$> ");
		}
		ft_printf("\n");
		free_list(&env_copy);
	}
	else
		ft_printf("%s unable to take arguments\n", *argv);
	// while (1);
	return (0);
}
