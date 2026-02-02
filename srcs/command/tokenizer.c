/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:44:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 17:55:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	t_dstr_arr	*add_token(t_dstr_arr *res, t_dstr *tokens)
{
	*res = str_arr_add_d(res, *tokens);
	if (res->strs == NULL)
		return (free_dstr(tokens), NULL);
	return (free_dstr(tokens), res);
}

static	t_dstr_arr	*add_tokens(t_dstr_arr *res, t_dstr *tokens)
{
	t_dstr_arr	token_arr;

	token_arr = str_split(cstr_d(*tokens), ' ');
	if (token_arr.strs == NULL)
		return (free_dstr(tokens), NULL);
	*res = str_arr_add_d_arr(res, &token_arr);
	if (res->strs == NULL)
		return (free_dstr(tokens), free_dstr_arr(&token_arr), NULL);
	return (free_dstr_arr(&token_arr), free_dstr(tokens), res);
}

t_dstr_arr	tokenize_raw_command(t_cstr command)
{
	t_dstr_arr	res;
	t_dstr		tokens;
	t_bool		in_quotes;
	t_cstr		before_quote;

	1 && (res = dstr_arr_s(0), in_quotes = FALSE);
	before_quote = str_findsub(command, cstr("'"));
	while (before_quote.s != NULL)
	{
		in_quotes = !in_quotes;
		tokens = str_sub(command, 0, (size_t)(before_quote.s - command.s));
		if (tokens.s == NULL)
			return (free_dstr_arr(&res), dstr_arr(NULL, 0));
		if (in_quotes == FALSE && add_tokens(&res, &tokens) == NULL)
			return (free_dstr_arr(&res), dstr_arr(NULL, 0));
		else if (in_quotes == TRUE && add_token(&res, &tokens) == NULL)
			return (free_dstr_arr(&res), dstr_arr(NULL, 0));
		command = str_cshift(command, (size_t)(before_quote.s - command.s) + 1);
		before_quote = str_findsub(command, cstr("'"));
	}
	tokens = str_sub(command, 0, (size_t)(before_quote.s - command.s));
	if (add_tokens(&res, &tokens) == NULL)
		return (free_dstr_arr(&res), dstr_arr(NULL, 0));
	return (res);
}
