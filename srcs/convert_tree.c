/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:34:12 by calle             #+#    #+#             */
/*   Updated: 2021/01/23 21:01:43 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	check_width(va_list ap, t_arg *arg)
{
	char	*tmp;
	int		n;

	if (c_in_s('*', arg->width) == 1)
	{
		free(arg->width);
		n = va_arg(ap, int);
		if (n == 0)
			arg->width_on = 0;
		if (n < 0 && c_in_s('-', arg->flags) == 0)
			arg->flags = ft_str_append(arg->flags, '-');
		tmp = ft_itoa(ft_abs(n));
		arg->width = ft_strdup(tmp);
		free(tmp);
	}
}

static void	check_prec(va_list ap, t_arg *arg)
{
	char	*tmp;
	int		n;

	if (c_in_s('*', arg->prec) == 1)
	{
		free(arg->prec);
		n = va_arg(ap, int);
		if (n < 0)
		{
			n = 0;
			arg->prec_on = 0;
			tmp = ft_strdup("");
		}
		else
			tmp = ft_itoa(n);
		arg->prec = ft_strdup(tmp);
		free(tmp);
	}
}

char		*convert_tree(va_list ap, t_arg *arg)
{
	check_width(ap, arg);
	check_prec(ap, arg);
	if (arg->type == 'c')
		return (convert_c(arg, ap));
	else if (arg->type == 's')
		return (convert_s(arg, ap));
	else if (arg->type == 'd' || arg->type == 'i')
		return (convert_d_i(arg, ap));
	else if (arg->type == 'u')
		return (convert_u(arg, ap));
	else if (arg->type == 'x' || arg->type == 'X')
		return (convert_x(arg, ap));
	else if (arg->type == 'p')
		return (convert_p(arg, ap));
	else if (arg->type == '%')
		return (convert_percent(arg));
	else
		return (NULL);
}
