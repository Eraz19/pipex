/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:00:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:55:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

t_pipes	*setup_pipes(t_pipes *res, t_program_args args)
{
	t_cstr_arr	args_;

	args_ = cstr_arr(args.argv + 1, args.argc - 1);
	dprintf(debug_fd, "Preparing args table for setup:\n");
	for (size_t i = 0; i < args_.len; ++i)
		dprintf(debug_fd, "  args_[%zu] = %s\n", i, args_.strs[i].s);
	if (args_.strs == NULL)
		return (NULL);
	dprintf(debug_fd, "Setting input file:\n");
	res->input_file = dstr_c(args_.strs[0]);
	if (res->input_file.s == NULL)
		return (free_cstr_arr(&args_), NULL);
	dprintf(debug_fd, "  input_file = %s\n", res->input_file.s);
	dprintf(debug_fd, "Setting output file:\n");
	res->output_file = dstr_c(args_.strs[args_.len - 1]);
	if (res->output_file.s == NULL)
		return (free_cstr_arr(&args_), NULL);
	dprintf(debug_fd, "  output_file = %s\n", res->output_file.s);
	dprintf(debug_fd, "Setting up commands:\n");
	if (setup_commands(res, &args_, args.envp) == NULL)
	{
		dprintf(debug_fd, "Failed to setup commands\n");
		dprintf(debug_fd, "Freeing args table and returning NULL\n");
		return (free_cstr_arr(&args_), NULL);
	}
	dprintf(debug_fd, "Setting up file descriptors:\n");
	if (setup_fds(res) == NULL)
		return (free_cstr_arr(&args_), NULL);
	printf_pipes(res);
	return (free_cstr_arr(&args_), res);
}
