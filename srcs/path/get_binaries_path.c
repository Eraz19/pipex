/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:39:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 11:27:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_bool	is_path_env_variable(t_cstr env_variable)
{
	t_cstr	match;

	match = str_findsub(env_variable, cstr("PATH="));
	if (match.s != NULL && match.s == env_variable.s)
		return (TRUE);
	return (FALSE);
}

static t_dstr_arr	get_binaries_path(const t_i8 **envp)
{
	size_t		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (is_path_env_variable(cstr(envp[i])) == TRUE)
			return (str_split(cstr(envp[i]), ':'));
		i++;
	}
	return (dstr_arr(NULL, 0));
}

t_dstr	get_binary_path(t_dstr command, const t_i8 **envp)
{
	size_t		i;
	t_dstr		*res;
	t_dstr		command_copy;
	t_dstr_arr	binaries_paths;

	binaries_paths = get_binaries_path(envp);
	if (binaries_paths.strs == NULL)
		return (dstr_s(0));
	i = 0;
	while (i < binaries_paths.len)
	{
		command_copy = dstr_d(command);
		if (command_copy.s == NULL)
			return (dstr_s(0));
		command_copy = str_insertc(&command_copy, cstr("/"), 0);
		if (command_copy.s == NULL)
			return (dstr_s(0));
		res = binaries_paths.strs + i;
		*res = str_insert(res, &command_copy, res->len);
		if (res->s == NULL || access(res->s, X_OK) == 0)
			return (*res);
		++i;
	}
	return (dstr_s(0));
}
