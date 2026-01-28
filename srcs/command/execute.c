/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:41:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 10:42:42 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_i8	**format_command_opts(t_dstr_arr command_opts)
{
	size_t	i;
	t_i8	**res;
	t_dstr	quote_trimmed;

	res = malloc(sizeof(t_i8 *) * (command_opts.len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < command_opts.len)
	{
		quote_trimmed = str_trim(&command_opts.strs[i], cstr("'"));
		if (quote_trimmed.s == NULL)
			return (free(res), NULL);
		1 && (res[i] = quote_trimmed.s, ++i);
	}
	res[i] = NULL;
	return (res);
}

static void	execute_command(t_command *command)
{
	t_dstr				command_path;
	t_i8				**command_opts;
	t_command_content	*command_content;

	command_content = command->content;
	dup2(command_content->input_fd, STDIN_FILENO);
	close(command_content->input_fd);
	dup2(command_content->output_fd, STDOUT_FILENO);
	close(command_content->output_fd);
	command_path = command_content->command;
	command_opts = format_command_opts(command_content->command_opts);
	if (command_opts == NULL)
		return ;
	execve(command_path.s, command_opts, NULL);
}

t_pipes	*execute_commands(t_pipes *pipes, size_t process_i, pid_t *pid)
{
	t_command			*command;
	t_command_content	*command_content;

	command = get(pipes->commands, process_i);
	if (command == NULL)
		return (free_pipes(pipes, free_command), NULL);
	command_content = command->content;
	*pid = fork();
	if (*pid < 0)
		return (free_pipes(pipes, free_command), NULL);
	else if (*pid == 0)
		execute_command(command);
	close(command_content->input_fd);
	close(command_content->output_fd);
	return (pipes);
}
