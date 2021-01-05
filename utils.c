/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:57:10 by calle             #+#    #+#             */
/*   Updated: 2021/01/05 18:18:54 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		char_in_str(char c, char *s)
{
	while(*s)
		if (c == *s++)
			return (1);
	return (0);
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
	if (!s | !c)
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
	s = NULL;
	return (r);
}


