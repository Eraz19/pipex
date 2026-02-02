/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:57:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 18:24:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>

// Global variable definition
t_i32	debug_fd;


static t_pipes	*execute_all_commands(t_pipes *pipes, t_program_args args)
{
	size_t			i;
	t_command		*command;
	t_command_node	*command_node;

	i = 0;
	while (i < pipes->commands.size)
	{
		command_node = get(pipes->commands, i);
		if (command_node == NULL)
			return (NULL);
		command = command_node->content;
		execute_command(pipes, command, args.envp);
		++i;
	}
	return (pipes);
}

static t_pipes	*wait_all_commands(t_pipes *pipes)
{
	size_t	i;

	i = 0;
	while (i < pipes->commands.size)
		1 && (wait_command(pipes), ++i);
	return (pipes);
}

static t_i32	get_pipe_status(t_pipes *pipes)
{
	t_command		*last_command;
	t_command_node	*last_command_node;

	last_command_node = get(pipes->commands, pipes->commands.size - 1);
	if (last_command_node == NULL)
		return (1);
	last_command = last_command_node->content;
	return (last_command->error_status);
}

t_i32	main(t_i32 argc, const t_i8 **argv, t_i8 **env)
{
	t_i32			res;
	t_program_args	args;
	t_pipes			pipes;
	
	debug_fd = open("/tmp/leak_debug.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (argc < 5)
		return (1);
	
	dprintf(debug_fd, "----------------------------------------\n");
	dprintf(debug_fd, "\nStarting Pipex with %d arguments\n", argc);
	dprintf(debug_fd, "args are : \n");
	for (t_i32 i = 0; i < argc; ++i)
		dprintf(debug_fd, "  argv[%d] = %s\n", i, argv[i]);

	dprintf(debug_fd, "Initializing pipes: \n");
	pipes = pipes_();
	1 && (args.argc = (size_t)argc, args.argv = argv, args.envp = env);
	dprintf(debug_fd, "Setting up pipes: \n");
	if (setup_pipes(&pipes, args) == NULL)
		return (free_pipes(&pipes, free_command), 1);
	if (execute_all_commands(&pipes, args) == NULL)
		return (free_pipes(&pipes, free_command), 1);
	if (wait_all_commands(&pipes) == NULL)
		return (free_pipes(&pipes, free_command), 1);
	res = get_pipe_status(&pipes);
	//res = 0;
	return (free_pipes(&pipes, free_command), res);
}
