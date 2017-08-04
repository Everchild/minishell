/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 16:08:28 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/04 16:05:45 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*static void			execute_child(char **cmd)
{
	ft_printf("cmd: %s\n", *cmd);
	ft_printf("1st arg: %s\n", *(cmd + 1));
	execve(*cmd, cmd, NULL);
}*/

/*static void			check_env_vars(t_dblist **save)
{
	(void **)save;
	ft_printf("check if there is PWD and SHLVL\n");
}*/

static void			handle_cmd(char **cmd)
{
	ft_printf("cmd:");
	while (cmd && *cmd)
	{
		ft_printf(" %s", *cmd);
		cmd++;
	}
	ft_printf("\n");
}

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
		cmd = NULL;
		get_env(&env_copy, env, argv[0]);
		if (!env_copy)
		{
			ft_printf("unable to get env\n");
			return (0);
		}
		// test env
		t_node		*node = env_copy->start;
		int			i = 0;
		while (node)
		{
			ft_printf("var %d: %s\n", i, node->content);
			node = node->next;
			i++;
		}
		// end test
		ft_printf("$> ");
		while (get_next_line(1, &buf))
		{
			tmp = ft_strtrimall(buf);
			cmd = ft_strsplit(tmp, ' ');
			ft_strdel(&buf);
			handle_cmd(cmd);
			free_tab(&cmd);
			ft_printf("$> ");
		}
		ft_printf("\n");
		free_list(&env_copy);
	}
	else
		ft_printf("%s unable to take arguments\n", *argv);
	/*	pid_t			pid;

		buf = NULL;
		cmd = NULL;
		ft_printf("Hello, I'm a shell! :D\n");
		ft_printf("$> ");
		while (get_next_line(1, &buf))
		{
		cmd = ft_strsplit(buf, ' ');
		pid = fork();
		if (pid < 0)
		ft_printf("error while creating child process\n");
		else if (pid == 0)
		{
		execute_child(cmd);
		}
		else
		{
		wait(0);
		ft_printf("$> ");
		}
		ft_strdel(&buf);
		}
		ft_putchar('\n');
		while (1);*/
	return (0);
}
