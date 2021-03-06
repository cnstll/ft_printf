/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:36:47 by calle             #+#    #+#             */
/*   Updated: 2021/01/23 20:54:58 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	handle_percent_modifiers(t_arg *arg)
{
	if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
	{
		arg->nb_zeros = arg->lf_pad;
		arg->lf_pad = 0;
	}
}

static void	arg_display_percent(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->width) && arg->l_arg < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
}

static char	*make_percent(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros;
	arg->l_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	while (arg->lf_pad-- > 0)
		r[i++] = ' ';
	while (arg->nb_zeros-- > 0)
		r[i++] = '0';
	while (arg->l_arg-- > 0)
		r[i++] = (arg->chain)[j++];
	while (arg->r_pad-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

char		*convert_percent(t_arg *arg)
{
	char	*ret;

	arg->chain = ft_strdup("%");
	arg_display_percent(arg);
	handle_percent_modifiers(arg);
	ret = make_percent(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}
