/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:39:12 by calle             #+#    #+#             */
/*   Updated: 2021/01/12 19:11:32 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void initiate_arg(t_arg *arg)
{
	arg->flags = "";
	arg->type = 0;
	arg->width = "";
	arg->precision = "";
	arg->l_pad = 0;
	arg->r_pad = 0;
	arg->len_displayed = 0;
	arg->len_arg = 0;
	arg->chain = "";
	arg->sign = 0;
	arg->nb_zeros = 0;
	arg->x_comp = "";
	arg->len_xcomp = 0;
	arg->ptr = NULL;
}

void initiate_config(t_config *config)
{
	config->types = "cspdiuxX%";
	config->flags = "-+0 #";
}

