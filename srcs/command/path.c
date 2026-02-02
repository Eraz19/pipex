/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:56:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/29 13:57:11 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_dstr	*build_binary_path(t_dstr *res, t_dstr path, t_cstr command)
{
	t_dstr	path_;

	path_ = dstr_d(path);
	if (path_.s == NULL)
		return (NULL);
	path_ = str_insertc(&path_, cstr("/"), path_.len);
	if (path_.s == NULL)
		return (NULL);
	path_ = str_insertc(&path_, command, path_.len);
	if (path_.s == NULL)
		return (NULL);
	return (*res = path_, res);
}

static t_dstr_arr	get_binaries_paths(t_i8 **envp)
{
	size_t	i;
	t_cstr	match;

	i = 0;
	while (envp[i] != NULL)
	{
		match = str_findsub(cstr(envp[i]), cstr("PATH="));
		if (match.s != NULL && match.s == envp[i])
			return (str_split(cstr(envp[i]), ':'));
		i++;
	}
	return (dstr_arr(NULL, 0));
}

t_dstr	get_command_path(t_dstr command, t_i8 **envp)
{
	size_t		i;
	t_dstr		res;
	t_dstr		binary_path;
	t_dstr_arr	binaries_paths;

	binaries_paths = get_binaries_paths(envp);
	if (binaries_paths.strs == NULL)
		return (dstr_s(0));
	i = 0;
	while (i < binaries_paths.len)
	{
		binary_path = binaries_paths.strs[i];
		if (build_binary_path(&res, binary_path, cstr_d(command)) == NULL)
			return (free_dstr_arr(&binaries_paths), dstr_s(0));
		if (res.s == NULL || access(res.s, X_OK) == 0)
			return (free_dstr_arr(&binaries_paths), res);
		1 && (free_dstr(&res), ++i);
	}
	return (free_dstr_arr(&binaries_paths), dstr_s(0));
}
