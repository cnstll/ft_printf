/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:57:10 by calle             #+#    #+#             */
/*   Updated: 2021/01/14 15:48:02 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		c_in_s(char c, char *s)
{
	while(*s)
		if (c == *s++)
			return (1);
	return (0);
}

unsigned int	ft_abs(int n)
{
	unsigned int nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

char	*strset(char c, unsigned int n)
{
	unsigned int	i;
	char			*s;

	i = 0;
	if (!(s = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (i < n)
		s[i++] = c;
	s[i] = 0;
	return (s);
}

char	*ft_str_append(char *s, char c)
{
	unsigned int	len;
	char			*r;
	int				i;

	len = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	if (!(r = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i++] = c;
	r[i] = '\0';
	if ((*s))
		free(s);
	return (r);
}
