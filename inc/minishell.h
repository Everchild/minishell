/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 16:08:41 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/06 13:30:56 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef enum		e_built
{
	B_CD,
	B_ECHO,
	B_ENV,
	B_SETENV,
	B_UNSETENV,
	B_EXIT,
	B_COUNT
}					t_built;

typedef struct		s_builtins
{
	t_built			built;
	char			*cmd;
	int				(*builtin)(t_dblist **, char **);
}					t_builtins;

void				get_env(t_dblist **save, char **orig, char *exe);
void				get_underscore_var(t_dblist **save, char *exe);
void				get_pwd_var(t_dblist **save);

void				handle_cmd(t_dblist **env, char **cmd);

#endif
