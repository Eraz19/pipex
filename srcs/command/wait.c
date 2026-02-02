/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:41:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 16:30:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>

void	wait_command(t_pipes *pipes)
{
	pid_t			pid;
	t_i32			status;
	t_command		*command;
	t_command_lst	command_lst;
	t_command_node	*command_node;

	pid = wait(&status);
	command_lst = filter(pipes->commands, find_command_by_pid, &pid);
	if (command_lst.nodes == NULL)
	{
		free_lst(&command_lst, NULL);
		perror("Wait failed");
		exit(EXIT_FAILURE);
	}
	command_node = command_lst.nodes;
	command = command_node->content;
	if (WIFEXITED(status))
		command->error_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		command->error_status = 128 + WTERMSIG(status);
	else
		command->error_status = status;
}
