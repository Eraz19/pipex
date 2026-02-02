/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:57:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:55:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft_list.h"
# include "libft_string.h"

typedef enum e_command_type
{
	STD,
	HEREDOC,
}	t_command_type;

typedef struct t_program_args
{
	size_t		argc;
	t_i8		**envp;
	const t_i8	**argv;
}	t_program_args;

typedef struct t_command
{
	pid_t			pid;
	t_command_type	type;
	t_i32			in_fd;
	t_i32			out_fd;
	t_dstr			command;
	t_dstr_arr		command_opts;
	t_i32			error_status;
}	t_command;
typedef t_node	t_command_node;
typedef t_lst	t_command_lst;

typedef struct t_pipes
{
	t_command_lst	commands;
	t_dstr			input_file;
	t_dstr			output_file;
}	t_pipes;

void	printf_pipes(t_pipes *pipes);

t_command_node	*command_node(void);
void			free_command(void *command);
void			wait_command(t_pipes *pipes);
t_dstr_arr		tokenize_raw_command(t_cstr command);
t_dstr			get_command_path(t_dstr command, t_i8 **env);
t_bool			find_command_by_pid(void *command, void *pid);
void			free_command_node(t_command_node **command_node);
void			execute_command(t_pipes *pipes, t_command *command, t_i8 **env);

t_pipes			pipes_(void);
t_pipes			*setup_fds(t_pipes *res);
t_pipes			*setup_pipes(t_pipes *res, t_program_args args);
void			free_pipes(t_pipes *pipes, void (*del)(void *));
t_pipes			*setup_commands(t_pipes *res, t_cstr_arr *args, t_i8 **env);

extern t_i32	debug_fd;

#endif