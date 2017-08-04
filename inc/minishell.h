/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 16:08:41 by sbrochar          #+#    #+#             */
/*   Updated: 2017/08/04 16:27:14 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

void				get_env(t_dblist **save, char **orig, char *exe);
void				get_underscore_var(t_dblist **save, char *exe);
void				get_pwd_var(t_dblist **save);

#endif
