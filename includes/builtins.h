/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:45:19 by veronikalub       #+#    #+#             */
/*   Updated: 2025/03/06 21:01:47 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>    // printf, perror
# include <unistd.h>   // getcwd write
# include <stdlib.h>   // malloc/free 

int		is_builtin(char *cmd);
int		ft_echo(char **args);
int		ft_cd(char **args, t_env **env);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
void	ft_exit(char **args, t_env *env);

#endif
