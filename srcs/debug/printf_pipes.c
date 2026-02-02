/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:05:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:21:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include <stdio.h>

void	printf_pipes(t_pipes *pipes)
{
	t_command		*command;
	t_command_node	*command_node;

	dprintf(debug_fd, "\n----------- pipes state -----------\n");
	dprintf(debug_fd, "Input file: %s\n", cstr_d(pipes->input_file).s);
	dprintf(debug_fd, "Output file: %s\n", cstr_d(pipes->output_file).s);
	dprintf(debug_fd, "Commands:\n");
	for (size_t i = 0; i < pipes->commands.size; ++i)
	{
		command_node = get(pipes->commands, i);
		if (command_node == NULL)
			continue ;
		command = command_node->content;
		dprintf(debug_fd, "  Command %zu:\n", i + 1);
		dprintf(debug_fd, "    Type: %s\n",
			(command->type == HEREDOC) ? "HEREDOC" : "STD");
		dprintf(debug_fd, "    Command: %s\n", cstr_d(command->command).s);
		for (size_t j = 0; j < command->command_opts.len; ++j)
			dprintf(debug_fd, "      Opt %zu: %s\n",
				j + 1, command->command_opts.strs[j].s);
		dprintf(debug_fd, "    In FD: %d\n", command->in_fd);
		dprintf(debug_fd, "    Out FD: %d\n", command->out_fd);
	}
	dprintf(debug_fd, "-----------------------------------\n");
}