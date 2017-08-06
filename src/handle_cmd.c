/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 10:03:55 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/06 13:30:10 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int			ft_cd(t_dblist **env, char **cmd)
{
	ft_printf("[%p] builtin %s\n", env, *cmd);
	return (0);
}

static int			ft_echo(t_dblist **env, char **cmd)
{
	ft_printf("[%p] builtin %s\n", env, *cmd);
	return (0);
}

static int			ft_env(t_dblist **env, char **cmd)
{
	ft_printf("[%p] builtin %s\n", env, *cmd);
	// test env
	t_node		*node = (*env)->start;
	int			i = 0;
	while (node)
	{
		ft_printf("var %d: %s\n", i, node->content);
		node = node->next;
		i++;
	}
	// end test
	return (0);
}

static int			ft_setenv(t_dblist **env, char **cmd)
{
	ft_printf("[%p] builtin %s\n", env, *cmd);
	return (0);
}

static int			ft_unsetenv(t_dblist **env, char **cmd)
{
	t_node			*cur;

	if (cmd)
	{
		cmd++;
		while (*cmd)
		{
			if (ft_strchr(*cmd, '='))
				return (-1);
			cur = (*env)->start;
			while (cur)
			{
				if (!ft_strncmp(cur->content, *cmd, ft_strlen(*cmd)))
				{
					remove_node(env, cur);
					break ;
				}
				cur = cur->next;
			}
			cmd++;
		}
	}
	return (0);
}

static int			ft_exit_sh(t_dblist **env, char **cmd)
{
	ft_printf("[%p] builtin %s\n", env, *cmd);
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

static void			search_and_exec_path(t_dblist **env, char **cmd, char **paths)
{
	char			**env_array;
	char			*tmp;

	tmp = NULL;
	env_array = listtotab(*env);
	while (*paths)
	{
		tmp = ft_strcjoin(*paths, *cmd, '/');
		if (tmp)
		{
			if (execve(tmp, cmd, env_array) != -1)
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
			search_and_exec_path(env, cmd, paths);
	}
	else
		ft_printf("minishell: %s: PATH not set\n", *cmd);
}

static void			execute_child(t_dblist **env, char **cmd)
{
	char			**env_array;

	if (ft_strchr(*cmd, '/'))
	{
		env_array = listtotab(*env);
		if (execve(*cmd, cmd, env_array) == -1)
			ft_printf("minishell: command not found: %s\n", *cmd);
	}
	else
		exec_relative_path(env, cmd);
}

void				handle_cmd(t_dblist **env, char **cmd)
{
	t_builtins		*builtins;
	pid_t			pid;
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
		builtins[i].builtin(env, cmd);
	else
	{
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
}
