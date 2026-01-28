/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:37:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 11:27:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*command_(void)
{
	t_command			*res;
	t_command_content	*content;

	content = malloc(sizeof(t_command_content));
	if (content == NULL)
		return (NULL);
	content->input_fd = -1;
	content->output_fd = -1;
	content->command = dstr_s(0);
	content->command_opts = dstr_arr(NULL, 0);
	res = node(content);
	return (res);
}
