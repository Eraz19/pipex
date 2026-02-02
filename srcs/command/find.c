/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:19:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/29 21:20:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	find_command_by_pid(void *command, void *pid)
{
	pid_t		pid_;
	t_command	command_;

	pid_ = *(pid_t *)pid;
	command_ = *(t_command *)command;
	return (command_.pid == pid_);
}
