/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:54:38 by saherrer          #+#    #+#             */
/*   Updated: 2025/04/18 16:20:56 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_first_argv(t_command *cmd, const char *value)
{
	cmd->argv = malloc(sizeof(char *) * 2);
	if (!cmd->argv)
		return (-300);
	cmd->argv[0] = ft_strdup(value);
	if (!cmd->argv[0])
		return (-300);
	cmd->argv[1] = NULL;
	return (0);
}

static int	append_to_existing_argv(t_command *cmd, const char *token_value)
{
	int		i;
	int		j;
	char	**new_argv;

	i = 0;
	j = 0;
	while (cmd->argv[i])
		i++;
	new_argv = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return (-300);
	while (j < i)
	{
		new_argv[j] = cmd->argv[j];
		j++;
	}
	new_argv[i] = ft_strdup(token_value);
	if (!new_argv[i])
		return (-300);
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (0);
}

int	add_to_argv(t_token *token, t_command *cmd, t_env **env_list)
{
	char	*cleaned;
	int		status;

	status = 0;
	var_expansion(token, *env_list);
	cleaned = remove_quotes(token->value);
	free(token->value);
	token->value = cleaned;
	if (!cmd->argv)
		status = init_first_argv(cmd, token->value);
	else
		status = append_to_existing_argv(cmd, token->value);
	token->type = 'd';
	return (status);
}
