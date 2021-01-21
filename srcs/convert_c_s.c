/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:47:52 by calle             #+#    #+#             */
/*   Updated: 2021/01/21 11:33:40 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void arg_display_s_c(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec < arg->l_arg && arg->prec_on == 1)
		arg->l_arg = arg->l_prec;
	if ((arg->prec_on == 1 && (arg->l_prec == 0														|| ft_strncmp(arg->chain, "(null)", 7) == 0)) && arg->l_prec < arg->l_arg)
	{
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (*(arg->width) && arg->l_arg < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
}

char *convert_s(t_arg *arg, va_list ap)
{
	char *ret;
	char *pad;
	char *tmp;

	tmp = va_arg(ap, char *);
	if (!tmp)
		arg->chain = ft_strdup("(null)");
	else
		arg->chain = ft_strdup(tmp);
	arg_display_s_c(arg);
	if (c_in_s('0', arg->flags) == 1 && arg->r_pad == 0)
		pad = strset('0', arg->lf_pad + arg->r_pad);
	else
		pad = strset(' ', arg->lf_pad + arg->r_pad);
	tmp = ft_substr(arg->chain, 0, arg->l_arg);
	if (arg->r_pad == 0)
		ret = ft_strjoin(pad, tmp);
	else
		ret = ft_strjoin(tmp, pad);
	arg->l_printed = ft_strlen(ret);
	free(tmp);
	free(pad);
	free_param(arg);
	return (ret);
}

static void make_c(t_arg *arg, char c)
{
	int		t;

	t = arg->l_arg + arg->r_pad + arg->lf_pad;
	arg->l_printed = t;
	t = arg->lf_pad;
	while (t-- > 0)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd(c, 1);
	t = arg->r_pad;
	while (t-- > 0)
		ft_putchar_fd(' ', 1);
}

void *convert_c(t_arg *arg, va_list ap)
{
	char c;

	c = (unsigned char )va_arg(ap, unsigned int);
	arg->chain = ft_str_append(arg->chain, c);
	arg_display_s_c(arg);
	make_c(arg, c);
	free(arg->chain);
	free_param(arg);
	return (NULL);
}

