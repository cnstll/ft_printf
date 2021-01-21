/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:29:25 by calle             #+#    #+#             */
/*   Updated: 2021/01/21 11:35:47 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void handle_printed_chain(int *ret, char *printed_chain, t_arg *arg)
{
			if(printed_chain != NULL || arg->l_printed > 0)
			{
				ft_putstr_fd(printed_chain, 1);
				(*ret) += arg->l_printed;
			}
			else
				(*ret) = -1;
			free(printed_chain);
}

void read_fmt(char *fmt, t_config *config, va_list ap, int *ret)
{
	int		i;
	char	*printed_chain;
	t_arg	*arg;

	i = 0;
	while (fmt[i] && *ret != -1)
	{
		if (fmt[i] == '%')
		{
			if (!(arg = (t_arg *)malloc(sizeof(t_arg))))
				return ;
			initiate_arg(arg);
			core_parsing(fmt, &i, arg, config);
			printed_chain = convert_tree(ap, arg);
			handle_printed_chain(ret, printed_chain, arg);
			free(arg);
		}
		else
		{
			ft_putchar_fd(fmt[i], 1);
			(*ret)++;
		}
		i++;
	}
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		ret;
	t_config *config;

	ret = 0;
	if (!*fmt)
		return (ret);
	if (!(config = (t_config *)malloc(sizeof(t_config))))
		return (-1);
	va_start(ap, fmt);
	initiate_config(config);
	read_fmt((char *)fmt, config, ap, &ret);
	va_end(ap);
	free(config);
	return (ret);
}

