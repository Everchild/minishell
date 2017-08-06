/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 16:08:28 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/05 12:03:47 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int			ft_cd(char **cmd)
{
	ft_printf("builtin %s\n", *cmd);
	return (0);
}

static int			ft_echo(char **cmd)
{
	ft_printf("builtin %s\n", *cmd);
	return (0);
}

static int			ft_env(char **cmd)
{
	ft_printf("builtin %s\n", *cmd);
	return (0);
}

static int			ft_setenv(char **cmd)
{
	ft_printf("builtin %s\n", *cmd);
	return (0);
}

static int			ft_unsetenv(char **cmd)
{
	ft_printf("builtin %s\n", *cmd);
	return (0);
}

static int			ft_exit_sh(char **cmd)
{
	ft_printf("builtin %s\n", *cmd);
	return (0);
}

static t_builtins	*get_builtins(void)
{
	static t_builtins	ret[B_COUNT] = {
		{ B_CD, "cd", &ft_cd },
		{ B_ECHO, "echo", &ft_echo },
		{ B_ENV, "env", &ft_env },
		{ B_SETENV, "setenv", &ft_setenv },
		{ B_UNSETENV, "unsetenv", &ft_unsetenv },
		{ B_EXIT, "exit", &ft_exit_sh },
	};

	return (ret);
}

static void			exec_relative_path(t_dblist **env, char **cmd)
{
	ft_printf("%s\n", (*env)->start->content);
	ft_printf("find path for %s\n", *cmd);
}

static void			execute_child(t_dblist **env, char **cmd)
{
	t_builtins		*builtins;
	int				i;

	builtins = get_builtins();
	i = 0;
	while (i < B_COUNT)
	{
		if (!ft_strcmp(*cmd, builtins[i].cmd))
			break ;
		i++;
	}
	if (i < B_COUNT)
		builtins[i].builtin(cmd);
	else if (ft_strchr(*cmd, '/'))
		execve(*cmd, cmd, NULL);
	else
		exec_relative_path(env, cmd);
}

static void			handle_cmd(t_dblist **env, char **cmd)
{
	// test cmd
	int				i = 0;
	ft_printf("cmd:");
	while (cmd && cmd[i])
	{
		ft_printf(" %s", cmd[i]);
		i++;
	}
	ft_printf("\n");
	// end test
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		ft_printf("%s: unable to launch process\n", *cmd);
	else if (pid == 0)
	{
		execute_child(env, cmd);
		exit(0);
	}
	else
		wait(0);
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
		tmp = NULL;
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
			handle_cmd(&env_copy, cmd);
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
