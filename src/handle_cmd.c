/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 10:03:55 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/06 10:13:21 by sbrochar         ###   ########.fr       */
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

static void			search_and_exec_path(/*t_dblist **env, */char **cmd, char **paths)
{
	char			*tmp;

	tmp = NULL;
	while (*paths)
	{
		tmp = ft_strcjoin(*paths, *cmd, '/');
		if (tmp)
		{
			if (execve(tmp, cmd, NULL) != -1)
				break ;
			ft_strdel(&tmp);
		}
		paths++;
	}
	if (tmp)
		ft_strdel(&tmp);
	else
		ft_printf("minishell: command not found: %s\n", *cmd);
}

static void			exec_relative_path(t_dblist **env, char **cmd)
{
	t_node			*cur;
	char			**paths;
	char			*tmp;

	cur = (*env)->start;
	paths = NULL;
	while (cur && ft_strncmp("PATH=", cur->content, 5))
		cur = cur->next;
	if (cur)
	{
		tmp = ft_strchr(cur->content, '=') + 1;
		paths = ft_strsplit(tmp, ':');
		if (paths)
			search_and_exec_path(cmd, paths);
	}
	else
		ft_printf("minishell: %s: PATH not set\n", *cmd);
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
	{
		if (execve(*cmd, cmd, NULL) == -1)
			ft_printf("minishell: command not found: %s\n", *cmd);
	}
	else
		exec_relative_path(env, cmd);
}

void				handle_cmd(t_dblist **env, char **cmd)
{
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
