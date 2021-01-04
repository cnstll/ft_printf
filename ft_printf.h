/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:50:08 by calle             #+#    #+#             */
/*   Updated: 2020/12/16 17:59:12 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdarg.h>

typedef struct	s_arg
{
	char	*flags; //"-+0 #"
	char	*type; //"cspdiuxX%"
	int		width; //number or *
	int		precision; //number or *
}				t_arg;

typedef struct	s_all_args
{
	t_arg	p;
}				t_all_args;

int		ft_printf(const char *s,...);
int		ft_init_parsing(const char *s, struct);

