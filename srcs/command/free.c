/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:41:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/27 15:21:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_command(void *command)
{
	if (command == NULL)
		return ;
	((t_command_content *)command)->input_fd = -1;
	((t_command_content *)command)->output_fd = -1;
	free_dstr(&(((t_command_content *)command)->command));
	free_dstr_arr(&(((t_command_content *)command)->command_opts));
	free(command);
}
