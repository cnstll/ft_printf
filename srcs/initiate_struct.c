/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:39:12 by calle             #+#    #+#             */
/*   Updated: 2021/01/21 11:30:17 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void initiate_arg(t_arg *arg)
{
	arg->flags = "";
	arg->type = 0;
	arg->width = "";
	arg->prec_on = 0;
	arg->prec = "";
	arg->lf_pad = 0;
	arg->r_pad = 0;
	arg->l_prec = 0;
	arg->l_width = 0;
	arg->l_arg = 0;
	arg->chain = "";
	arg->sign = 0;
	arg->nb_zeros = 0;
	arg->p_x_pref = "";
	arg->x_init = 0;
	arg->ln_p_x_pref = 0;
	arg->l_printed = 0;
}

void initiate_config(t_config *config)
{
	config->types = "cspdiuxX%";
	config->flags = "-+0 #";
}

