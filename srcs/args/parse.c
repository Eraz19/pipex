/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:00:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 13:49:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_command_content	*add_opt(t_command_content *res, t_dstr opt)
{
	t_dstr	opt_;

	opt_ = dstr_d(opt);
	if (opt_.s == NULL)
		return (NULL);
	res->command_opts = str_arr_add_d(&res->command_opts, opt_);
	if (res->command_opts.strs == NULL)
		return (NULL);
	return (res);
}

static t_command_content	*add_opt_quote(t_command_content *res, t_dstr opt)
{
	t_dstr	opt_;
	t_dstr	quote_opt;

	opt_ = dstr_d(opt);
	if (opt_.s == NULL)
		return (NULL);
	opt_ = str_insertc(&opt_, cstr(" "), 0);
	if (opt_.s == NULL)
		return (NULL);
	quote_opt = res->command_opts.strs[res->command_opts.len - 1];
	quote_opt = str_insert(&quote_opt, &opt_, quote_opt.len);
	if (quote_opt.s == NULL)
		return (free_dstr(&opt_), NULL);
	res->command_opts.strs[res->command_opts.len - 1] = quote_opt;
	free_dstr(&opt_);
	return (res);
}

static t_command_content	*parse_opts(t_command_content *res, t_dstr_arr opts)
{
	size_t	i;
	t_dstr	opt;
	t_bool	in_quotes;

	1 && (res->command_opts = dstr_arr_s(0), in_quotes = FALSE, i = 0);
	while (i <= opts.size - 1)
	{
		opt = opts.strs[i];
		if (in_quotes == FALSE && add_opt(res, opt) == NULL)
			return (NULL);
		else if (in_quotes == TRUE && add_opt_quote(res, opt) == NULL)
			return (NULL);
		if (opt.s[0] == '\'' && in_quotes == FALSE)
			in_quotes = TRUE;
		else if (opt.s[opt.len - 1] == '\'' && in_quotes == TRUE)
			in_quotes = FALSE;
		i++;
		
	}
	return (res);
}

static t_command	*parse_command(t_command *res, t_cstr command_string)
{
	t_command_content	*command_content;
	t_dstr_arr			split_command_args;

	command_content = (t_command_content *)res->content;
	split_command_args = str_split(command_string, ' ');
	if (split_command_args.strs == NULL)
		return (NULL);
	command_content->command = dstr_d(split_command_args.strs[0]);
	if (command_content->command.s == NULL)
		return (free_dstr_arr(&split_command_args), NULL);
	if (parse_opts(command_content, split_command_args) == NULL)
		return (free_dstr_arr(&split_command_args), NULL);
	free_dstr_arr(&split_command_args);
	return (res);
}

t_pipes	*parse_args(t_pipes *res, size_t argc, const t_i8 **argv)
{
	size_t		i;
	t_cstr_arr	args;
	t_command	*command;

	i = 1;
	args = cstr_arr(argv + 1, argc - 1);
	if (args.strs == NULL)
		return (NULL);
	res->input_file = dstr_c(args.strs[0]);
	res->output_file = dstr_c(args.strs[args.len - 1]);
	if (res->input_file.s == NULL || res->output_file.s == NULL)
		return (free_cstr_arr(&args), NULL);
	while (i < args.len - 1)
	{
		command = command_();
		if (command == NULL)
			return (free_cstr_arr(&args), NULL);
		res->commands = lst_insert(&res->commands, command, res->commands.size);
		if (parse_command(command, args.strs[i]) == NULL)
			return (free_cstr_arr(&args), NULL);
		++i;
	}
	return (free_cstr_arr(&args), res);
}
