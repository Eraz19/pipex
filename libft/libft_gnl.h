/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:53:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/30 18:13:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GNL_H
# define LIBFT_GNL_H

# include "libft_list.h"
# include "libft_string.h"

typedef struct t_reader
{
	t_i32			fd;
	t_u8			buf[BUF_SIZE];
	ssize_t			read_count;
	size_t			start;
}	t_reader;
typedef struct t_reader_node
{
	t_reader				*content;
	struct t_reader_node	*next;
}	t_reader_node;
typedef t_lst	t_readers;

t_dstr			get_next_line(t_u32 fd, t_readers *readers, t_cstr delim);

t_reader_node	*reader_(t_i32 fd);
void			free_reader(void *reader);

#endif