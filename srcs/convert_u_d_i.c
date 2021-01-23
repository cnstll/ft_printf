/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:47:19 by calle             #+#    #+#             */
/*   Updated: 2021/01/23 17:49:49 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>
static void handle_d_i_u_modifiers(t_arg *arg)
{
	if (!*(arg->prec) && arg->prec_on == 0)
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->lf_pad;
			arg->lf_pad = 0;
		}
	}
	if ((c_in_s('+', arg->flags) == 0 && c_in_s(' ', arg->flags) == 1 && arg->sign > -1))
	{
		arg->lf_pad = arg->lf_pad + 1;
		if (arg->r_pad > 0)
			arg->r_pad = arg->r_pad - 1;
		if (arg->nb_zeros > 0)
			arg->nb_zeros -= 1;
	}
}

static void arg_display_nb(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec > arg->l_arg)
		arg->nb_zeros = arg->l_prec - arg->l_arg;
	if (arg->prec_on == 1 && arg->l_prec == 0 && ft_atoi(arg->chain) == 0)
	{
		free(arg->chain);
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (arg->l_prec == 1)
		arg->l_prec = 0;
	if (*(arg->width) && arg->l_arg + arg->nb_zeros < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
}

static char *make_d_i_u(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros + ft_abs(arg->sign);
	arg->l_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	while (arg->lf_pad-- > 0)
		r[i++] = ' ';
	if (arg->sign == -1)
		r[i++] = '-';
	if (arg->sign == 1)
		r[i++] = '+';
	while (arg->nb_zeros-- > 0)
		r[i++] = '0';
	while (arg->l_arg-- > 0)
		r[i++] = (arg->chain)[j++];
	while (arg->r_pad-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

char *convert_d_i(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;
	int				n;

	n = va_arg(ap, int);
	nb = 0;
	if (n < 0)
	{
		nb = -n;
		arg->sign = -1;
	}
	else
		nb = (unsigned int)n;
	if (c_in_s('+', arg->flags) == 1 && arg->sign != -1)
		arg->sign = 1;
	arg->chain = ft_itoa(nb);
	arg_display_nb(arg);
	handle_d_i_u_modifiers(arg);
	ret = make_d_i_u(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}

char *convert_u(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	arg->chain = ft_itoa(nb);
	arg_display_nb(arg);
	handle_d_i_u_modifiers(arg);
	ret = make_d_i_u(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}
