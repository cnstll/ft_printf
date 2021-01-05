/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:39:12 by calle             #+#    #+#             */
/*   Updated: 2021/01/04 18:41:44 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void initiate_arg(t_arg *arg)
{
	arg->flags = "";
	arg->type = 0;
	arg->width = "";
	arg->precision = "";
}

void initiate_config(t_config *config)
{
	config->types = "cspdiuxX%";
	config->flags = "-+0 #";
}

