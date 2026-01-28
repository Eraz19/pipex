/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/26 14:05:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include "libft_types.h"
# include "libft_buffer.h"

typedef struct t_dstring
{
	t_i8	*s;
	size_t	len;
	size_t	size;
}	t_dstr;
typedef struct t_dstring_arr
{
	t_dstr	*strs;
	size_t	len;
	size_t	size;
}	t_dstr_arr;
typedef struct t_cstring
{
	const t_i8	*s;
	size_t		len;
	size_t		size;
}	t_cstr;
typedef struct t_cstring_arr
{
	t_cstr	*strs;
	size_t	len;
	size_t	size;
}	t_cstr_arr;

t_cstr		cstr_d(t_dstr str);
t_cstr		cstr(const t_i8 *s);
t_cstr_arr	cstr_arr_s(size_t count);
t_cstr_arr	cstr_arr(const t_i8 **strs, size_t count);

t_dstr		dstr_d(t_dstr str);
t_dstr		dstr_c(t_cstr str);
t_dstr		dstr_s(size_t size);
t_dstr_arr	dstr_arr_s(size_t count);
t_dstr_arr	dstr_arr(t_i8 **strs, size_t count);

void		free_dstr(t_dstr *str);
void		free_dstr_arr(t_dstr_arr *str_arr);
void		free_cstr_arr(t_cstr_arr *str_arr);

t_i32		str_cmp(t_cstr str1, t_cstr str2);

t_cstr		str_findchr(t_cstr str, t_i32 c);
ssize_t		str_findindex(t_cstr str, t_i8 c);
t_cstr		str_findsub(t_cstr str, t_cstr sub);
t_cstr		str_findlastchr(t_cstr str, t_i32 c);
ssize_t		str_findlastindex(t_cstr str, t_i8 c);

t_dstr		str_insert(t_dstr *str, t_dstr *insrt, size_t i);
t_dstr		str_insertc(t_dstr *str, t_cstr insrt, size_t i);

t_dstr		str_from_buf(t_dbuf *buf);

t_dstr		str_from_char(t_i8 c);

t_dstr		str_from_int(t_i32 n, t_cstr base, t_bool sign);
t_bool		str_to_int(t_i32 *res, t_cstr nptr, t_cstr base);

t_dstr		str_from_long(t_i64 n, t_cstr base, t_bool sign);
t_bool		str_to_long(t_i64 *res, t_cstr nptr, t_cstr base);

t_dstr		str_map(t_dstr *str, t_i8 (*f)(t_u32, t_i8));
void		str_foreach(t_cstr str, void (*f)(t_u32, t_i8));

void		str_print(t_cstr str, t_i32 fd);

t_dstr		str_repeat(t_cstr str, size_t n);

t_cstr		str_cshift(t_cstr str, size_t offset);
t_cstr		str_dshift(t_dstr str, size_t offset);

t_dstr_arr	str_split(t_cstr str, t_i8 c);

t_dstr		str_sub(t_cstr str, size_t start, size_t len);

t_dstr		str_trim(t_dstr *str, t_cstr set);

t_dstr_arr	str_arr_add_d(t_dstr_arr *arr, t_dstr str);
t_cstr_arr	str_arr_add_c(t_cstr_arr *arr, t_cstr str);

#endif
