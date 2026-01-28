/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:49:34 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 11:28:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

static t_command	*set_command_path(t_command *res, const t_i8 **envp)
{
	t_dstr				command_path;
	t_command_content	*command_content;

	command_content = res->content;
	command_path = get_binary_path(command_content->command, envp);
	if (command_path.s == NULL)
		return (free_dstr(&command_path), NULL);
	free_dstr(&command_content->command);
	command_content->command = command_path;
	return (res);
}

static t_commands	*set_in_file_fd(t_commands *res, t_dstr file_name)
{
	t_command			*command;
	t_i32				open_file_flag;
	t_command_content	*command_content;

	command = get(*res, 0);
	if (command == NULL)
		return (NULL);
	open_file_flag = O_RDONLY;
	command_content = command->content;
	command_content->input_fd = open(file_name.s, open_file_flag);
	if (command_content->input_fd < 0)
		return (NULL);
	return (res);
}

static t_commands	*set_out_file_fd(t_commands *res, t_dstr file_name)
{
	t_command			*command;
	t_i32				open_file_flag;
	t_command_content	*command_content;

	command = get(*res, res->size - 1);
	if (command == NULL)
		return (NULL);
	command_content = command->content;
	open_file_flag = O_CREAT | O_WRONLY | O_TRUNC;
	command_content->output_fd = open(file_name.s, open_file_flag, 0644);
	if (command_content->output_fd < 0)
		return (NULL);
	return (res);
}

static t_commands	*set_files_fds(t_commands *res, t_pipes pipes)
{
	if (set_in_file_fd(res, pipes.input_file) == NULL)
		return (NULL);
	if (set_out_file_fd(res, pipes.output_file) == NULL)
		return (NULL);
	return (res);
}

t_pipes	*setup_pipes(t_pipes *pipes, const t_i8 **envp)
{
	size_t				i;
	t_command			*command;
	t_command_content	*command_content;
	t_i32				pipe_fds[2];

	i = 0;
	if (set_files_fds(&pipes->commands, *pipes) == NULL)
		return (NULL);
	while (i < pipes->commands.size)
	{
		command = get(pipes->commands, i);
		if (command == NULL)
			return (NULL);
		command_content = command->content;
		if (set_command_path(command, envp) == NULL)
			return (NULL);
		if (command_content->input_fd == -1)
			command_content->input_fd = pipe_fds[0];
		if (i < pipes->commands.size - 1)
			pipe(pipe_fds);
		if (command_content->output_fd == -1)
			command_content->output_fd = pipe_fds[1];
		++i;
	}
	return (pipes);
}
