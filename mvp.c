#include <stdio.h>
#include "ft_printf.h"

void free_all(t_arg *arg)
{
	if (*(arg->precision))
		free(arg->precision);
	if (*(arg->flags))
		free(arg->flags);
	if (*(arg->width))
		free(arg->width);
}

void parse_precision(char *s, int *i, t_arg *arg)
{
	if (s[*i] == '.')
	{
		arg->prec_on = 1;
		if (s[++(*i)] == '*')
			arg->precision = ft_str_append(arg->precision, s[(*i)++]);
		else
		{
			while (ft_isdigit(s[*i]))
				arg->precision = ft_str_append(arg->precision, s[(*i)++]);
		}
	}
}

void core_parsing(char *s, int *i, t_arg *arg, t_config *config)
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

void arg_display_s(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	arg->len_prec = ft_atoi(arg->precision);
	arg->len_width = ft_atoi(arg->width);
	if (*(arg->precision) && arg->len_prec < arg->len_arg && arg->prec_on == 1)
		arg->len_arg = arg->len_prec;
	if ((arg->prec_on == 1 && (arg->len_prec == 0 || ft_strncmp(arg->chain, "(null)", 7) == 0)) && arg->len_prec < arg->len_arg)
	{
		arg->chain = ft_strdup("");
		arg->len_arg = 0;
	}
	if (*(arg->width) && arg->len_arg < ft_abs(arg->len_width))
	{
		if (c_in_s('-', arg->flags) == 1)
		{
			arg->r_pad = ft_atoi(arg->width);
			if (arg->r_pad > arg->len_arg)
				arg->r_pad = arg->r_pad - arg->len_arg;
		}
		else
		{
			arg->l_pad = ft_atoi(arg->width);
			if (arg->l_pad > arg->len_arg)
				arg->l_pad = arg->l_pad - arg->len_arg;
		}
	}
}

char *convert_s(t_arg *arg, va_list ap)
{
	char *ret;
	char *pad;
	char *tmp;

	tmp = va_arg(ap, char *);
	if (!tmp)
		arg->chain = ft_strdup("(null)");
	else
		arg->chain = ft_strdup(tmp);
	arg_display_s(arg);
	pad = strset(' ', arg->l_pad + arg->r_pad);
	tmp = ft_substr(arg->chain, 0, arg->len_arg);
	if (arg->r_pad == 0)
		ret = ft_strjoin(pad, tmp);
	else
		ret = ft_strjoin(tmp, pad);
	arg->len_printed = ft_strlen(ret);
	free(tmp);
	free(pad);
	free_all(arg);
	return (ret);
}

void arg_display_c(t_arg *arg)
{
	arg->len_arg = 1;
	arg->len_prec = ft_atoi(arg->precision);
	arg->len_width = ft_atoi(arg->width);
	if (*(arg->precision) && arg->len_prec < arg->len_arg && arg->prec_on == 1)
		arg->len_arg = arg->len_prec;
	if (arg->prec_on == 1 && arg->len_prec == 0 && arg->len_prec < arg->len_arg)
	{
		arg->chain = ft_strdup("");
		arg->len_arg = 0;
	}
	if (*(arg->width) && arg->len_arg < ft_abs(arg->len_width))
	{
		if (c_in_s('-', arg->flags) == 1)
		{
			arg->r_pad = ft_atoi(arg->width);
			if (arg->r_pad > arg->len_arg)
				arg->r_pad = arg->r_pad - arg->len_arg;
		}
		else
		{
			arg->l_pad = ft_atoi(arg->width);
			if (arg->l_pad > arg->len_arg)
				arg->l_pad = arg->l_pad - arg->len_arg;
		}
	}
}

void make_c(t_arg *arg, char c)
{
	int		t;

	t = arg->len_arg + arg->r_pad + arg->l_pad;
	arg->len_printed = t;
	t = arg->l_pad;
	while (t-- > 0)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd(c, 1);
	t = arg->r_pad;
	while (t-- > 0)
		ft_putchar_fd(' ', 1);
}

void *convert_c(t_arg *arg, va_list ap)
{
	char c;

	c = (unsigned char )va_arg(ap, unsigned int);
	arg->chain = ft_str_append(arg->chain, c);
	arg_display_c(arg);
	make_c(arg, c);
	free(arg->chain);
	free_all(arg);
	return (NULL);
}

void handle_d_i_u_modifiers(t_arg *arg)
{
	if (!*(arg->precision) || arg->prec_on == 0)
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->l_pad;
			arg->l_pad = 0;
		}
		if (c_in_s('+', arg->flags) == 0 && c_in_s(' ', arg->flags) == 1)
		{
			arg->nb_zeros = arg->nb_zeros - 1;
			arg->l_pad = arg->l_pad + 1 - arg->sign * arg->sign;
			if (arg->l_pad >= 1)
				arg->r_pad = arg->r_pad - 1 + arg->sign * arg->sign;
			else
				arg->r_pad = arg->sign * arg->sign;
		}
	}
}

void arg_display_nb(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	arg->len_prec = ft_atoi(arg->precision);
	arg->len_width = ft_atoi(arg->width);
	if (*(arg->precision) && arg->len_prec > arg->len_arg)
		arg->nb_zeros = arg->len_prec - arg->len_arg;
	if (arg->prec_on == 1 && arg->len_prec == 0 && ft_atoi(arg->chain) == 0)
	{
		free(arg->chain);
		arg->chain = ft_strdup("");
		arg->len_arg = 0;
	}
	if (arg->len_prec == 1)
		arg->len_prec = 0;
	if (arg->len_width == 1 && ft_atoi(arg->chain) != 0)
		arg->len_width = 0;
	if (*(arg->width) && arg->len_arg + arg->nb_zeros < ft_abs(arg->len_width))
	{
		if (c_in_s('-', arg->flags) == 1)
		{
			arg->r_pad = ft_atoi(arg->width);
			if (arg->r_pad > arg->len_arg)
				arg->r_pad = arg->r_pad - arg->len_arg - arg->nb_zeros;
			arg->r_pad = arg->r_pad - ft_abs(arg->sign);
		}
		else
		{
			arg->l_pad = ft_atoi(arg->width);
			if (arg->l_pad > arg->len_arg)
				arg->l_pad = arg->l_pad - arg->len_arg - arg->nb_zeros;
			arg->l_pad = arg->l_pad - ft_abs(arg->sign);
		}
	}
}

char *make_d_i_u(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->len_arg + arg->r_pad + arg->l_pad + arg->nb_zeros + arg->sign * arg->sign;
	arg->len_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	t = arg->l_pad;
	while (t-- > 0)
		r[i++] = ' ';
	if (arg->sign == -1)
		r[i++] = '-';
	if (arg->sign == 1)
		r[i++] = '+';
	t = arg->nb_zeros;
	while (t-- > 0)
		r[i++] = '0';
	t = arg->len_arg;
	while (t-- > 0)
		r[i++] = (arg->chain)[j++];
	t = arg->r_pad;
	while (t-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

char *convert_d_i(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;
	int				n;

	n = va_arg(ap, int);
	nb = 0;
	if (n < 0)
	{
		nb = -(n + 1);
		nb = nb + 1;
		arg->sign = -1;
	}
	else
		nb = (unsigned int)n;
	if (c_in_s('+', arg->flags) == 1 && arg->sign != -1)
		arg->sign = 1;
	arg->chain = ft_itoa(nb);
	arg_display_nb(arg);
	handle_d_i_u_modifiers(arg);
	ret = make_d_i_u(arg);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

char *convert_u(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	arg->chain = ft_itoa(nb);
	arg_display_nb(arg);
	handle_d_i_u_modifiers(arg);
	ret = make_d_i_u(arg);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

void handle_p_modifiers(t_arg *arg)
{
	if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
	{
		arg->nb_zeros = arg->l_pad;
		arg->l_pad = 0;
	}
	if (arg->len_xcomp > 0)
	{
		if (arg->l_pad >= 2)
			arg->l_pad = arg->l_pad - 2;
		else
			arg->l_pad = 0;
		if (arg->r_pad >= 2)
			arg->r_pad = arg->r_pad - 2;
		else
			arg->r_pad = 0;
		if (arg->nb_zeros >= 2)
			arg->nb_zeros = arg->nb_zeros - 2;
		else
			arg->nb_zeros = 0;
	}
}

char *make_p(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->len_arg + arg->r_pad + arg->l_pad + arg->nb_zeros + arg->len_xcomp;
	arg->len_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	t = arg->l_pad;
	while (t-- > 0)
		r[i++] = ' ';
	t = ft_strlen(arg->x_comp);
	while (t-- > 0)
		r[i++] = (arg->x_comp)[j++];
	t = arg->nb_zeros;
	while (t-- > 0)
		r[i++] = '0';
	t = arg->len_arg;
	j =  0;
	while (t-- > 0)
		r[i++] = (arg->chain)[j++];
	t = arg->r_pad;
	while (t-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

void arg_display_p(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	if (c_in_s('-', arg->flags) == 1)
	{
		arg->r_pad = ft_atoi(arg->width);
		if (arg->r_pad > arg->len_arg)
			arg->r_pad = arg->r_pad - arg->len_arg;
	}
	else
	{
		arg->l_pad = ft_atoi(arg->width);
		if (arg->l_pad > arg->len_arg)
			arg->l_pad = arg->l_pad - arg->len_arg;
	}
}

char *convert_p(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;

	nb = va_arg(ap, unsigned long);
	arg->chain = ft_itoa_base(nb, "0123456789abcdef");
	arg->x_comp = "0x";
	arg->len_xcomp = ft_strlen(arg->x_comp);
	arg_display_p(arg);
	handle_p_modifiers(arg);
	ret = make_p(arg);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

void handle_x_X_modifiers(t_arg *arg)
{
	if (!(*arg->precision) || arg->prec_on == 0)
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->l_pad;
			arg->l_pad = 0;
		}
	}
	if (c_in_s('#', arg->flags) == 1)
	{
		if (!*(arg->precision))
			arg->nb_zeros = arg->nb_zeros - 2;
		if (arg->l_pad >= 2)
			arg->l_pad = arg->l_pad - 2;
		else
			arg->l_pad = 0;
		if (arg->r_pad >= 2)
			arg->r_pad = arg->r_pad - 2;
		else
			arg->r_pad = 0;
		arg->len_xcomp = 2;
		if (arg->type == 'x')
			arg->x_comp = "0x";
		else
			arg->x_comp = "0X";
		}
}

void arg_display_x_X(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	arg->len_width = ft_abs(ft_atoi(arg->width));
	arg->len_prec = ft_atoi(arg->precision);
	if (*(arg->precision) && arg->len_prec > arg->len_arg)
		arg->nb_zeros = arg->len_prec - arg->len_arg;
	if (arg->prec_on == 1 && arg->len_prec == 0 && arg->x_init == 0)
	{
		arg->chain = ft_strdup("");
		arg->len_arg = 0;
	}
	if (arg->len_width == 1 && arg->x_init != 0)
		arg->len_width = 0;
	if (*(arg->width) && arg->len_width > arg->len_arg + arg->nb_zeros)
	{
		if (c_in_s('-', arg->flags) == 1)
		{
			arg->r_pad = arg->len_width;
			if (arg->r_pad > arg->len_arg)
				arg->r_pad = arg->r_pad - arg->len_arg - arg->nb_zeros;
		}
		else
		{
			arg->l_pad = arg->len_width;
			if (arg->l_pad > arg->len_arg)
				arg->l_pad = arg->l_pad - arg->len_arg - arg->nb_zeros;
		}
	}
}

char *make_x_X(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->len_arg + arg->r_pad + arg->l_pad + arg->nb_zeros + arg->len_xcomp;
	arg->len_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	t = arg->l_pad;
	while (t-- > 0)
		r[i++] = ' ';
	t = ft_strlen(arg->x_comp);
	while (t-- > 0)
		r[i++] = (arg->x_comp)[j++];
	t = arg->nb_zeros;
	while (t-- > 0)
		r[i++] = '0';
	t = arg->len_arg;
	j = 0;
	while (t-- > 0)
		r[i++] = (arg->chain)[j++];
	t = arg->r_pad;
	while (t-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

char *convert_x_X(t_arg *arg, va_list ap)
{
	char			*ret;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	arg->x_init = nb;
	if (arg->type == 'x')
		arg->chain = ft_itoa_base(nb, "0123456789abcdef");
	if (arg->type == 'X')
		arg->chain = ft_itoa_base(nb, "0123456789ABCDEF");
	arg_display_x_X(arg);
	handle_x_X_modifiers(arg);
	ret = make_x_X(arg);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

char *convert_percent(t_arg *arg)
{
	char			*ret;

	ret = ft_strdup("%");
	arg->len_printed = 1;
	free_all(arg);
	return (ret);
}

void check_arg(va_list ap, t_arg *arg)
{
	char			*tmp;
	int				n;

	if (c_in_s('*', arg->width) ==  1)
	{
		free(arg->width);
		n = va_arg(ap, int);
		if (n < 0 && c_in_s('-', arg->flags) == 0)
			arg->flags = ft_str_append(arg->flags, '-');
		tmp = ft_itoa(ft_abs(n));
		arg->width = ft_strdup(tmp);
		free(tmp);
	}
	if (c_in_s('*', arg->precision) ==  1)
	{
		free(arg->precision);
		n = va_arg(ap, int);
		if (n < 0)
		{
			n = 0;
			arg->prec_on = 0;
		}
		tmp = ft_itoa(n);
		arg->precision = ft_strdup(tmp);
		free(tmp);
	}
}

char *preparing_ret(va_list ap, t_arg *arg)
{
		check_arg(ap, arg);
		if (arg->type == 'c')
			return (convert_c(arg, ap));
		else if (arg->type == 's')
			return (convert_s(arg, ap));
		else if (arg->type == 'd' || arg->type == 'i')
			return (convert_d_i(arg, ap));
		else if (arg->type == 'u')
			return (convert_u(arg, ap));
		else if (arg->type == 'x' || arg->type == 'X')
			return (convert_x_X(arg, ap));
		else if (arg->type == 'p')
			return (convert_p(arg, ap));
		else if (arg->type == '%')
			return (convert_percent(arg));
		else
			return (NULL);
}



void read_fmt(char *fmt, t_config *config, va_list ap, int *ret)
{
	int	i;
	char *print;
	t_arg *arg;

	i = 0;
	while (fmt[i] && *ret != -1)
	{
		if (fmt[i] == '%')
		{
			if (!(arg = (t_arg *)malloc(sizeof(t_arg))))
				return ;
			initiate_arg(arg);
			core_parsing(fmt, &i, arg, config);
			print = preparing_ret(ap, arg);
			ft_putstr_fd(print, 1);
			if(print != NULL && arg->len_printed > 0)
			{
				ft_putstr_fd(print, 1);
				(*ret) += arg->len_printed;
			}
			else
				(*ret) = -1;
			free(print);
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
