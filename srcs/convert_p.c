/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:40:22 by calle             #+#    #+#             */
/*   Updated: 2021/01/23 20:59:28 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	handle_p_modifiers(t_arg *arg)
{
	if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
	{
		arg->nb_zeros = arg->lf_pad;
		arg->lf_pad = 0;
	}
	if (arg->ln_p_x_pref > 0)
		modify_padding_x_p(arg);
}

static char	*make_p(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros +
												arg->ln_p_x_pref;
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

static void	arg_display_p(t_arg *arg, unsigned int nb)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec > arg->l_arg)
		arg->nb_zeros = arg->l_prec - arg->l_arg;
	if (arg->prec_on == 1 && arg->l_prec == 0 && nb == 0)
	{
		free(arg->chain);
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (*(arg->width) && arg->l_arg < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
}

char		*convert_p(t_arg *arg, va_list ap)
{
	char			*ret;
	uintptr_t		nb;

	nb = (uintptr_t)va_arg(ap, void *);
	arg->chain = ft_itoa_base(nb, "0123456789abcdef");
	arg->p_x_pref = "0x";
	arg->ln_p_x_pref = ft_strlen(arg->p_x_pref);
	arg_display_p(arg, nb);
	handle_p_modifiers(arg);
	ret = make_p(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}
