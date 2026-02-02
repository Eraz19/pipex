/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:41:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:55:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_command(void *command)
{
	t_command	*command_;

	if (command == NULL)
		return ;
	command_ = (t_command *)command;
	command_->pid = -1;
	command_->in_fd = -1;
	command_->out_fd = -1;
	command_->error_status = 0;
	free_dstr(&command_->command);
	free_dstr_arr(&command_->command_opts);
	free(command);
}

void	free_command_node(t_command_node **command_node)
{
	if (command_node == NULL)
		return ;
	free_command((*command_node)->content);
	free(*command_node);
	*command_node = NULL;
}
