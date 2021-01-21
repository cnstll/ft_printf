/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:38:32 by calle             #+#    #+#             */
/*   Updated: 2021/01/21 11:34:04 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void handle_x_modifiers(t_arg *arg)
{
	if (!(*arg->prec) || arg->prec_on == 0)
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->lf_pad;
			arg->lf_pad = 0;
		}
	}
	if (c_in_s('#', arg->flags) == 1)
	{
		if (!*(arg->prec))
			arg->nb_zeros = arg->nb_zeros - 2;
		modify_padding_x_p(arg);
		arg->ln_p_x_pref = 2;
		if (arg->type == 'x')
			arg->p_x_pref = "0x";
		else
			arg->p_x_pref = "0X";
		}
}

static void arg_display_x(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec > arg->l_arg)
		arg->nb_zeros = arg->l_prec - arg->l_arg;
	if (arg->prec_on == 1 && arg->l_prec == 0 && arg->x_init == 0)
	{
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (arg->l_width == 1 && arg->x_init != 0)
		arg->l_width = 0;
	if (*(arg->width) && arg->l_width > arg->l_arg + arg->nb_zeros)
		generate_lf_r_padding(arg);
}

static char *make_x(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros + arg->ln_p_x_pref;
	arg->l_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	while (arg->lf_pad-- > 0)
		r[i++] = ' ';
	while (arg->ln_p_x_pref-- > 0)
		r[i++] = (arg->p_x_pref)[j++];
	while (arg->nb_zeros-- > 0)
		r[i++] = '0';
	j = 0;
	while (arg->l_arg-- > 0)
		r[i++] = (arg->chain)[j++];
	while (arg->r_pad-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

char *convert_x(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	arg->x_init = nb;
	if (arg->type == 'x')
		arg->chain = ft_itoa_base(nb, "0123456789abcdef");
	if (arg->type == 'X')
		arg->chain = ft_itoa_base(nb, "0123456789ABCDEF");
	arg_display_x(arg);
	handle_x_modifiers(arg);
	ret = make_x(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}

