/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:57:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 11:27:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft_list.h"
# include "libft_string.h"

typedef struct t_command_content
{
	t_i32		input_fd;
	t_i32		output_fd;
	t_dstr		command;
	t_dstr_arr	command_opts;
}	t_command_content;
typedef t_node	t_command;
typedef t_lst	t_commands;
typedef struct t_pipes
{
	t_commands	commands;
	t_dstr		input_file;
	t_dstr		output_file;
}	t_pipes;

t_command	*command_(void);
void		free_command(void *command);
t_pipes		*execute_commands(t_pipes *pipes, size_t process_i, pid_t *pid);

t_pipes		pipes_(void);
void		free_pipes(t_pipes *pipes, void (*del)(void *));
t_pipes		*setup_pipes(t_pipes *pipes, const t_i8 **envp);

t_pipes		*parse_args(t_pipes *res, size_t argc, const t_i8 **argv);

t_dstr		get_binary_path(t_dstr command, const t_i8 **envp);

#endif