/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:57:10 by calle             #+#    #+#             */
/*   Updated: 2021/01/13 15:55:05 by calle            ###   ########.fr       */
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
	if ((*s))
		free(s);
	return (r);
}

/*char			*ft_strjoin_mem(char *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*r;
	size_t	i;
	size_t	j;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	while (s1 && i < l1 && s1[j])
		r[i++] = s1[j++];
	i = 0;
	while (s2 && i < l2 && s2[i])
		r[l1++] = s2[i++];
	r[l1] = '\0';
	if (!(*s1))
		free(s1);
	return (r);
}*/
