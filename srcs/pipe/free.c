/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:05:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/27 15:10:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipes(t_pipes *pipes, void (*del)(void *))
{
	free_dstr(&(pipes->input_file));
	free_dstr(&(pipes->output_file));
	free_lst(&(pipes->commands), del);
}
