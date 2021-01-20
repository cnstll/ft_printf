/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:50:08 by calle             #+#    #+#             */
/*   Updated: 2021/01/15 17:01:29 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "libft/libft.h"
typedef struct	s_arg
{
	char			*flags;
	char			type;
	char			*width;
	int				prec_on;
	char			*prec;
	unsigned int	lf_pad;
	unsigned int	r_pad;
	unsigned int	l_prec;
	unsigned int	l_width;
	unsigned int	l_arg;
	char			*chain;
	int				sign;
	int			    nb_zeros;
	char			*p_x_pref;
	unsigned int	x_init;
	int				ln_p_x_pref;
	int				l_printed;
}				t_arg;

typedef struct	s_config
{
	char *types;
	char *flags;
}				t_config;

int				ft_printf(const char *fmt,...);
void			initiate_arg(t_arg *arg);
void			initiate_config(t_config *config);
char			*ft_str_append(char *s, char c);
int				c_in_s(char c, char *s);
char			*strset(char c, unsigned int n);
char			*ft_itoa_base(long long unsigned int nbr, char *base);
unsigned int	ft_abs(int n);
#endif
