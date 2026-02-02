/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:05:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:31:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdio.h>

void	free_pipes(t_pipes *pipes, void (*del)(void *))
{
	dprintf(debug_fd, "Freeing pipes\n");

	free_dstr(&(pipes->input_file));
	free_dstr(&(pipes->output_file));
	free_lst(&(pipes->commands), del);
}
