/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:57:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 13:36:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

t_i32	main(t_i32 argc, const t_i8 **argv, const t_i8 **envp)
{
	size_t	i;
	pid_t	pid;
	t_pipes	pipes;

	if (argc != 5)
		return (1);
	pipes = pipes_();
	if (parse_args(&pipes, (size_t)argc, argv) == NULL)
		return (free_pipes(&pipes, free_command), 1);
	if (setup_pipes(&pipes, envp) == NULL)
		return (free_pipes(&pipes, free_command), 1);
	i = 0;
	while (i < pipes.commands.size)
		1 && (execute_commands(&pipes, i, &pid), ++i);
	i = 0;
	while (i < pipes.commands.size)
		1 && (wait(NULL), ++i);
	free_pipes(&pipes, free_command);
	return (0);
}
