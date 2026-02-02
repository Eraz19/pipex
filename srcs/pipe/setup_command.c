/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:37:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 18:22:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdio.h>

static t_command	*set_heredoc_command(t_command *command, t_cstr delim)
{
	command->type = HEREDOC;
	command->command = dstr_c(delim);
	if (command->command.s == NULL)
		return (NULL);
	return (command);
}

static t_command	*set_std_command(t_command *command, t_cstr arg, t_i8 **env)
{
	t_dstr_arr	tokens;

	dprintf(debug_fd, "Tokenizing raw command: %s\n", arg.s);
	tokens = tokenize_raw_command(arg);
	for (size_t i = 0; i < tokens.len; ++i)
		dprintf(debug_fd, "  tokens[%zu] = %s\n", i, tokens.strs[i].s);
	if (tokens.strs == NULL)
	{
		dprintf(debug_fd, "Failed to tokenize raw command return NULL\n");
		return (NULL);
	}
	dprintf(debug_fd, "Getting command path for: %s\n", tokens.strs[0].s);
	command->command = get_command_path(tokens.strs[0], env);
	if (command->command.s == NULL)
	{
		dprintf(debug_fd, "Failed to get command path return NULL\n");
		return (free_dstr_arr(&tokens), command);
	}
	dprintf(debug_fd, "  command path = %s\n", command->command.s);
	command->command_opts = tokens;
	dprintf(debug_fd, "  Successfully set up standard command\n");
	return (command);
}

t_pipes	*setup_commands(t_pipes *res, t_cstr_arr *args, t_i8 **env)
{
	size_t			i;
	t_command		*command;
	t_command_node	*new_node;

	i = 1;
	while (i < args->len - 1)
	{
		dprintf(debug_fd, "Setting up command %zu: %s\n", i, args->strs[i].s);
		new_node = command_node();
		if (new_node == NULL)
			return (NULL);
		dprintf(debug_fd, "  Created new command node\n");
		command = (t_command *)new_node->content;
		if (i == 1 && str_cmp(cstr_d(res->input_file), cstr("here_doc")) == 0)
		{
			if (set_heredoc_command(command, args->strs[i]) == NULL)
			{
				free_command_node(&new_node);
				dprintf(debug_fd, "  Failed to set up heredoc command return NULL\n");
				return (NULL);
			}
		}
		else
		{
			dprintf(debug_fd, "  Setting up standard command\n");
			if (set_std_command(command, args->strs[i], env) == NULL)
			{
				free_command_node(&new_node);
				dprintf(debug_fd, "  Failed to set up standard command return NULL\n");
				return (NULL);
			}
		}
		dprintf(debug_fd, "  Inserting command into pipes commands list\n");
		lst_insert(&res->commands, new_node, res->commands.size);
		dprintf(debug_fd, "  Successfully set up command\n");
		++i;
	}
	return (res);
}
