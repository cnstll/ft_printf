/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:50:08 by calle             #+#    #+#             */
/*   Updated: 2021/01/10 17:00:32 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "/home/nath/42projects/ft_printf/libft/libft.h"

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
	int     zero_displayed;
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
#endif
