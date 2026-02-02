/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:41:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 16:53:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_gnl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	close_other_fds(void *command, void *target)
{
	t_command	*target_;
	t_command	*command_;

	command_ = (t_command *)command;
	target_ = (t_command *)target;
	if (command_ != target_)
	{
		if (command_->in_fd >= 0)
			close(command_->in_fd);
		if (command_->out_fd >= 0)
			close(command_->out_fd);
	}
}

static void	on_redirection_failed(t_pipes *pipes, t_command *command)
{
	perror("Dup2 failed");
	if (command->in_fd >= 0)
		close(command->in_fd);
	if (command->out_fd >= 0)
		close(command->out_fd);
	free_pipes(pipes, free_command);
	exit(EXIT_FAILURE);
}

static t_command	*fill_heredoc_pipe(t_command *command)
{
	t_readers		readers;
	t_cstr			delimiter;
	t_dstr			stdin_input;
	t_reader_node	*reader_node;

	readers = lst_();
	reader_node = reader_(STDIN_FILENO);
	if (reader_node == NULL)
		return (NULL);
	readers = lst_insert(&readers, (t_node *)reader_node, 0);
	delimiter = cstr(command->command.s);
	stdin_input = get_next_line(STDIN_FILENO, &readers, delimiter);
	if (stdin_input.s == NULL)
		return (free_lst(&readers, free_reader), NULL);
	stdin_input = str_trim(&stdin_input, delimiter);
	str_print(cstr_d(stdin_input), command->out_fd);
	1 && (close(command->out_fd), command->out_fd = -1);
	return (free_lst(&readers, free_reader), free_dstr(&stdin_input), command);
}

static void	children_process(t_pipes *pipes, t_command *command, t_i8 **env)
{
	t_i8	**command_opts;

	lst_foreach(pipes->commands, close_other_fds, command);
	if (dup2(command->in_fd, STDIN_FILENO) == -1)
		on_redirection_failed(pipes, command);
	if (command->in_fd >= 0)
		close(command->in_fd);
	if (dup2(command->out_fd, STDOUT_FILENO) == -1)
		on_redirection_failed(pipes, command);
	if (command->out_fd >= 0)
		close(command->out_fd);
	if (command->command.s == NULL)
	{
		free_pipes(pipes, free_command);
		perror("Command not found");
		exit(127);
	}
	command_opts = dstr_arr_unwrap(command->command_opts);
	if (command_opts == NULL)
	{
		free_pipes(pipes, free_command);
		exit(EXIT_FAILURE);
	}
	execve(command->command.s, command_opts, env);
	perror(command->command_opts.strs[0].s);
	free_pipes(pipes, free_command);
	exit(EXIT_FAILURE);
}

void	execute_command(t_pipes *pipes, t_command *command, t_i8 **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		free_pipes(pipes, free_command);
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (command->type == HEREDOC)
		{
			lst_foreach(pipes->commands, close_other_fds, command);
			fill_heredoc_pipe(command);
			free_pipes(pipes, free_command);
			exit(EXIT_SUCCESS);
		}
		else
			children_process(pipes, command, env);
	}
	command->pid = pid;
	if (command->in_fd >= 0)
		close(command->in_fd);
	if (command->out_fd >= 0)
		close(command->out_fd);
}
