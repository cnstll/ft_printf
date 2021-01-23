/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:44:15 by calle             #+#    #+#             */
/*   Updated: 2021/01/23 20:56:17 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	modify_padding_x_p(t_arg *arg)
{
	if (arg->lf_pad >= 2)
		arg->lf_pad = arg->lf_pad - 2;
	else
		arg->lf_pad = 0;
	if (arg->r_pad >= 2)
		arg->r_pad = arg->r_pad - 2;
	else
		arg->r_pad = 0;
}

void	generate_lf_r_padding(t_arg *arg)
{
	if (c_in_s('-', arg->flags) == 1)
	{
		arg->r_pad = ft_atoi(arg->width);
		if (arg->r_pad >= arg->l_arg)
			arg->r_pad = arg->r_pad - arg->l_arg - arg->nb_zeros;
		arg->r_pad = arg->r_pad - ft_abs(arg->sign);
	}
	else
	{
		arg->lf_pad = ft_atoi(arg->width);
		if (arg->lf_pad >= arg->l_arg)
			arg->lf_pad = arg->lf_pad - arg->l_arg - arg->nb_zeros;
		arg->lf_pad = arg->lf_pad - ft_abs(arg->sign);
	}
}

void	free_param(t_arg *arg)
{
	if (*(arg->prec))
		free(arg->prec);
	if (*(arg->flags))
		free(arg->flags);
	if (*(arg->width))
		free(arg->width);
}

void	set_len_parameter(t_arg *arg)
{
	if (arg->type == 'c')
		arg->l_arg = 1;
	else
		arg->l_arg = ft_strlen(arg->chain);
	arg->l_prec = ft_abs(ft_atoi(arg->prec));
	arg->l_width = ft_abs(ft_atoi(arg->width));
}
