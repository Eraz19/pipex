/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:37:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 15:54:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command_node	*command_node(void)
{
	t_command_node	*res;
	t_command		*content;

	content = malloc(sizeof(t_command));
	if (content == NULL)
		return (NULL);
	content->pid = -1;
	content->type = STD;
	content->in_fd = -1;
	content->out_fd = -1;
	content->error_status = 0;
	content->command = dstr_s(0);
	content->command_opts = dstr_arr(NULL, 0);
	res = node(content);
	return (res);
}
