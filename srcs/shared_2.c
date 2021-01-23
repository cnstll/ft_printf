/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:14:26 by calle             #+#    #+#             */
/*   Updated: 2021/01/23 21:12:34 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	parse_precision(char *s, int *i, t_arg *arg)
{
	if (s[*i] == '.')
	{
		arg->prec_on = 1;
		if (s[++(*i)] == '*')
			arg->prec = ft_str_append(arg->prec, s[(*i)++]);
		else
		{
			while (ft_isdigit(s[*i]))
				arg->prec = ft_str_append(arg->prec, s[(*i)++]);
		}
	}
}

void		core_parsing(char *s, int *i, t_arg *arg, t_config *config)
{
	while (c_in_s((s[++(*i)]), config->flags) == 1)
		if (!c_in_s(s[*i], arg->flags))
			arg->flags = ft_str_append(arg->flags, s[*i]);
	parse_precision(s, i, arg);
	if (s[*i] == '*')
		arg->width = ft_str_append(arg->width, s[(*i)++]);
	else
	{
		while (ft_isdigit(s[*i]))
			arg->width = ft_str_append(arg->width, s[(*i)++]);
	}
	parse_precision(s, i, arg);
	if (c_in_s((s[*i]), config->types) == 1)
		arg->type = s[*i];
}
