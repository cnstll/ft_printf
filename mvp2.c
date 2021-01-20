#include <stdio.h>
#include "ft_printf.h"

void free_param(t_arg *arg)
{
	if (*(arg->prec))
		free(arg->prec);
	if (*(arg->flags))
		free(arg->flags);
	if (*(arg->width))
		free(arg->width);
}

void set_len_parameter(t_arg *arg)
{
	if (arg->type == 'c')
		arg->l_arg = 1;
	else
		arg->l_arg = ft_strlen(arg->chain);
	arg->l_prec = ft_abs(ft_atoi(arg->prec));
	arg->l_width = ft_abs(ft_atoi(arg->width));
}

void parse_precision(char *s, int *i, t_arg *arg)
{
	if (s[*i] == '.')
	{
		arg->prec_on = 1;
		if (s[++(*i)] == '*')
			arg->prec = ft_str_append(arg->prec, s[(*i)++]);
		else
		{
			while (ft_isdigit(s[*i]))
				arg->prec = ft_str_append(arg->prec, s[(*i)++]);
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

void generate_lf_r_padding(t_arg *arg)
{
		if (c_in_s('-', arg->flags) == 1)
		{
			arg->r_pad = ft_atoi(arg->width);
			if (arg->r_pad >= arg->l_arg)
				arg->r_pad = arg->r_pad - arg->l_arg - arg->nb_zeros;
			arg->r_pad = arg->r_pad - ft_abs(arg->sign);
		}
		else
		{
			arg->lf_pad = ft_atoi(arg->width);
			if (arg->lf_pad >= arg->l_arg)
				arg->lf_pad = arg->lf_pad - arg->l_arg - arg->nb_zeros;
			arg->lf_pad = arg->lf_pad - ft_abs(arg->sign);
		}
}

void arg_display_s_c(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec < arg->l_arg && arg->prec_on == 1)
		arg->l_arg = arg->l_prec;
	if ((arg->prec_on == 1 && (arg->l_prec == 0 || ft_strncmp(arg->chain, "(null)", 7) == 0)) && arg->l_prec < arg->l_arg)
	{
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (*(arg->width) && arg->l_arg < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
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
	arg_display_s_c(arg);
	if (c_in_s('0', arg->flags) == 1 && arg->r_pad == 0)
		pad = strset('0', arg->lf_pad + arg->r_pad);
	else
		pad = strset(' ', arg->lf_pad + arg->r_pad);
	tmp = ft_substr(arg->chain, 0, arg->l_arg);
	if (arg->r_pad == 0)
		ret = ft_strjoin(pad, tmp);
	else
		ret = ft_strjoin(tmp, pad);
	arg->l_printed = ft_strlen(ret);
	free(tmp);
	free(pad);
	free_param(arg);
	return (ret);
}

void make_c(t_arg *arg, char c)
{
	int		t;

	t = arg->l_arg + arg->r_pad + arg->lf_pad;
	arg->l_printed = t;
	t = arg->lf_pad;
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
	arg_display_s_c(arg);
	make_c(arg, c);
	free(arg->chain);
	free_param(arg);
	return (NULL);
}

void handle_d_i_u_modifiers(t_arg *arg)
{
	if (!*(arg->prec) || arg->prec_on == 0)
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->lf_pad;
			arg->lf_pad = 0;
		}
		if (c_in_s('+', arg->flags) == 0 && c_in_s(' ', arg->flags) == 1)
		{
			if (arg->nb_zeros > 0)
				arg->nb_zeros = arg->nb_zeros - 1;
			arg->lf_pad = arg->lf_pad + 1 - ft_abs(arg->sign);
			if (arg->r_pad > 0)
				arg->r_pad = arg->r_pad - 1 + ft_abs(arg->sign);
			else
				arg->r_pad = ft_abs(arg->sign);
		}
	}
}

void arg_display_nb(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec > arg->l_arg)
		arg->nb_zeros = arg->l_prec - arg->l_arg;
	if (arg->prec_on == 1 && arg->l_prec == 0 && ft_atoi(arg->chain) == 0)
	{
		free(arg->chain);
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (arg->l_prec == 1)
		arg->l_prec = 0;
	if (*(arg->width) && arg->l_arg + arg->nb_zeros < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
}

char *make_d_i_u(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros + ft_abs(arg->sign);
	arg->l_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	while (arg->lf_pad-- > 0)
		r[i++] = ' ';
	if (arg->sign == -1)
		r[i++] = '-';
	if (arg->sign == 1)
		r[i++] = '+';
	while (arg->nb_zeros-- > 0)
		r[i++] = '0';
	while (arg->l_arg-- > 0)
		r[i++] = (arg->chain)[j++];
	while (arg->r_pad-- > 0)
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
		nb = -n;
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
	free_param(arg);
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
	free_param(arg);
	return (ret);
}

void modify_padding_x_X_p(t_arg *arg)
{
		if (arg->lf_pad >= 2)
			arg->lf_pad = arg->lf_pad - 2;
		else
			arg->lf_pad = 0;
		if (arg->r_pad >= 2)
			arg->r_pad = arg->r_pad - 2;
		else
			arg->r_pad = 0;
}

void handle_p_modifiers(t_arg *arg)
{
	if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
	{
		arg->nb_zeros = arg->lf_pad;
		arg->lf_pad = 0;
	}
	if (arg->ln_p_x_pref > 0)
		modify_padding_x_X_p(arg);
}

char *make_p(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros + arg->ln_p_x_pref;
	arg->l_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	while (arg->lf_pad-- > 0)
		r[i++] = ' ';
	while (arg->ln_p_x_pref-- > 0)
		r[i++] = (arg->p_x_pref)[j++];
	while (arg->nb_zeros-- > 0)
		r[i++] = '0';
	j =  0;
	while (arg->l_arg-- > 0)
		r[i++] = (arg->chain)[j++];
	while (arg->r_pad-- > 0)
		r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

void arg_display_p(t_arg *arg, unsigned int nb)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec > arg->l_arg)
		arg->nb_zeros = arg->l_prec - arg->l_arg;
	if (arg->prec_on == 1 && arg->l_prec == 0 && nb == 0)
	{
		free(arg->chain);
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (*(arg->width) && arg->l_arg < ft_abs(arg->l_width))
		generate_lf_r_padding(arg);
}

char *convert_p(t_arg *arg, va_list ap)
{
	char			*ret;
	uintptr_t		nb;

	nb = (uintptr_t)va_arg(ap, void *);
	arg->chain = ft_itoa_base(nb, "0123456789abcdef");
	arg->p_x_pref = "0x";
	arg->ln_p_x_pref = ft_strlen(arg->p_x_pref);
	arg_display_p(arg, nb);
	handle_p_modifiers(arg);
	ret = make_p(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}

void handle_x_X_modifiers(t_arg *arg)
{
	if (!(*arg->prec) || arg->prec_on == 0)
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->lf_pad;
			arg->lf_pad = 0;
		}
	}
	if (c_in_s('#', arg->flags) == 1)
	{
		if (!*(arg->prec))
			arg->nb_zeros = arg->nb_zeros - 2;
		modify_padding_x_X_p(arg);
		arg->ln_p_x_pref = 2;
		if (arg->type == 'x')
			arg->p_x_pref = "0x";
		else
			arg->p_x_pref = "0X";
		}
}

void arg_display_x_X(t_arg *arg)
{
	set_len_parameter(arg);
	if (*(arg->prec) && arg->l_prec > arg->l_arg)
		arg->nb_zeros = arg->l_prec - arg->l_arg;
	if (arg->prec_on == 1 && arg->l_prec == 0 && arg->x_init == 0)
	{
		arg->chain = ft_strdup("");
		arg->l_arg = 0;
	}
	if (arg->l_width == 1 && arg->x_init != 0)
		arg->l_width = 0;
	if (*(arg->width) && arg->l_width > arg->l_arg + arg->nb_zeros)
		generate_lf_r_padding(arg);
}

char *make_x_X(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->l_arg + arg->r_pad + arg->lf_pad + arg->nb_zeros + arg->ln_p_x_pref;
	arg->l_printed = t;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	while (arg->lf_pad-- > 0)
		r[i++] = ' ';
	while (arg->ln_p_x_pref-- > 0)
		r[i++] = (arg->p_x_pref)[j++];
	while (arg->nb_zeros-- > 0)
		r[i++] = '0';
	j = 0;
	while (arg->l_arg-- > 0)
		r[i++] = (arg->chain)[j++];
	while (arg->r_pad-- > 0)
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
	free_param(arg);
	return (ret);
}

char *convert_percent(t_arg *arg)
{
	char			*ret;

	arg->chain = ft_strdup("%");
	arg_display_nb(arg);
	handle_d_i_u_modifiers(arg);
	ret = make_d_i_u(arg);
	free(arg->chain);
	free_param(arg);
	return (ret);
}

void check_width(va_list ap, t_arg *arg)
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
}

void check_prec(va_list ap, t_arg *arg)
{
	char			*tmp;
	int				n;

	if (c_in_s('*', arg->prec) ==  1)
	{
		free(arg->prec);
		n = va_arg(ap, int);
		if (n < 0)
		{
			n = 0;
			arg->prec_on = 0;
		}
		tmp = ft_itoa(n);
		arg->prec = ft_strdup(tmp);
		free(tmp);
	}
}

char *preparing_ret(va_list ap, t_arg *arg)
{
		check_width(ap, arg);
		check_prec(ap, arg);
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
			printed_chain = preparing_ret(ap, arg);
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
