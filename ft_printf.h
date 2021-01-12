/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:50:08 by calle             #+#    #+#             */
/*   Updated: 2021/01/12 19:11:03 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "../ft_printf/libft/libft.h"
typedef struct	s_arg
{
	char	*flags; //"-+0 #"
	char	type; //"cspdiuxX%"
	char	*width; //number or *
	char	*precision; //number or *
	int		l_pad;
	int		r_pad;
	int		len_displayed;
	int		len_arg;
	char	*chain;
	int		sign;
	int     nb_zeros;
	char	*x_comp;
	int		len_xcomp;
	void	*ptr;
}				t_arg;

typedef struct	s_config
{
	char *types;
	char *flags;
}				t_config;

int		ft_printf(const char *fmt,...);
void	initiate_arg(t_arg *arg);
void	initiate_config(t_config *config);
char	*ft_str_append(char *s, char c);
int		char_in_str(char c, char *s);
char	*strset(char c, unsigned int n);
char	*ft_itoa_base(unsigned int nbr, char *base);
#endif
