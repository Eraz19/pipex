/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:36:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:55:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>

static t_command	*set_start_fds(t_command *res, t_pipes *pipes, t_i32 fds[2])
{
	t_i32	fd;

	if (pipe(fds) == -1)
		return (NULL);
	dprintf(debug_fd, "Created pipe for first command: [%d, %d]\n",
		fds[0], fds[1]);
	res->out_fd = fds[1];
	if (res->type != HEREDOC)
	{
		fd = open(pipes->input_file.s, O_RDONLY);
		dprintf(debug_fd, "Opening input file: %s with fd %d\n",
			cstr_d(pipes->input_file).s, fd);
		res->in_fd = fd;
	}
	return (res);
}

static t_command	*set_end_fds(t_command *res, t_pipes *pipes, t_i32 fds[2])
{
	t_i32			flag;
	t_command		*first_command;
	t_command_node	*first_command_node;
	t_i32			fd;

	first_command_node = get(pipes->commands, 0);
	if (first_command_node == NULL)
		return (NULL);
	first_command = first_command_node->content;
	if (first_command->type == HEREDOC)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	else
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	res->in_fd = fds[0];
	fd = open(pipes->output_file.s, flag, 0644);
	dprintf(debug_fd, "Opening output file: %s with fd %d\n",
		cstr_d(pipes->output_file).s, fd);
	res->out_fd = fd;
	return (res);
}

t_pipes	*setup_fds(t_pipes *res)
{
	size_t			i;
	t_command		*command;
	t_i32			pipes_fds[2];

	command = get(res->commands, 0)->content;
	if (set_start_fds(command, res, pipes_fds) == NULL)
		return (NULL);
	i = 1;
	while (i < res->commands.size - 1)
	{
		command = get(res->commands, i)->content;
		command->in_fd = pipes_fds[0];
		if (pipe(pipes_fds) == -1)
			return (NULL);
		dprintf(debug_fd, "Created pipe for command %zu: [%d, %d]\n",
			i + 1, pipes_fds[0], pipes_fds[1]);
		command->out_fd = pipes_fds[1];
		++i;
	}
	command = get(res->commands, i)->content;
	if (set_end_fds(command, res, pipes_fds) == NULL)
		return (NULL);
	return (res);
}
