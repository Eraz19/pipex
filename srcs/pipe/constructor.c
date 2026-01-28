/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:48:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/28 11:27:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipes	pipes_(void)
{
	t_pipes	res;

	res.commands = lst_();
	res.input_file = dstr_s(0);
	res.output_file = dstr_s(0);
	return (res);
}
