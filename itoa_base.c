/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:40:17 by calle             #+#    #+#             */
/*   Updated: 2021/01/13 15:01:56 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_base_valid(char *bse)
{
	int				i;
	int				j;

	i = 0;
	while (bse[i])
	{
		if (!bse[0] || !bse[1])
			return (0);
		if (bse[i] == '-' || bse[i] == '+')
			return (0);
		j = i + 1;
		while (bse[j])
			if (bse[i] == bse[j++])
				return (0);
		i++;
	}
	return (i);
}

char	*ft_strrev(char *s)
{
	size_t			len;
	char			tmp;
	unsigned int	i;

	len = ft_strlen(s);
	i = 0;
	while (s[i] && i < len / 2)
	{
		tmp = s[len - i - 1];
		s[len - i - 1] = s[i];
		s[i] = tmp;
		i++;
	}
	s[len] = 0;
	return (s);
}

char	*ft_itoa_base(long long unsigned int nbr, char *base)
{
	int						bse;
	char					*ret;
	long long unsigned int	t_nbr;

	bse = ft_base_valid(base);
	ret = "";
	if (bse == 0)
		return (NULL);
	t_nbr = nbr;
	while (t_nbr != 0)
	{
		ret = ft_str_append(ret, base[(t_nbr % bse)]);
		t_nbr = t_nbr / bse;
	}
	if (nbr == 0)
		ret = ft_str_append(ret, '0');
	return (ft_strrev(ret));
}

