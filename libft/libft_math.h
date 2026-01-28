/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 20:11:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

# include "libft_types.h"

t_u32	abs_i(t_i32 c);
t_u64	abs_l(t_i64 c);

t_bool	is_prime_i(t_u32 nb);
t_bool	is_prime_l(t_u64 nb);

t_u32	pow_i(t_i32 nbr, t_u32 p);
t_u64	pow_l(t_i64 nbr, t_u32 p);

#endif
