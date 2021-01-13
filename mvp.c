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

void arg_display_char(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	arg->len_displayed = ft_atoi(arg->precision);
	if (*(arg->precision) && arg->len_displayed < arg->len_arg)
		arg->len_arg = arg->len_displayed;
	if (c_in_s('-', arg->flags) == 1)
	{
		arg->r_pad = ft_atoi(arg->width);
		if (arg->r_pad > arg->len_arg)
			arg->r_pad = arg->r_pad - arg->len_arg;
		arg->l_pad = 0;
	}
	else
	{
		arg->l_pad = ft_atoi(arg->width);
		if (arg->l_pad > arg->len_arg)
			arg->l_pad = arg->l_pad - arg->len_arg;
		arg->r_pad = 0;
	}
}

void handle_d_i_modifiers(t_arg *arg)
{
	if (!(*arg->precision))
	{
		if (c_in_s('-', arg->flags) == 0 && c_in_s('0', arg->flags) == 1)
		{
			arg->nb_zeros = arg->l_pad;
			arg->l_pad = 0;
		}
		if (c_in_s('+', arg->flags) == 0 && c_in_s(' ', arg->flags) == 1)
		{
			arg->nb_zeros = arg->nb_zeros - 1;
			arg->l_pad = arg->l_pad + 1 + arg->sign;
			arg->r_pad = arg->r_pad - 1 - arg->sign;
		}
	}
}

void handle_x_X_modifiers(t_arg *arg)
{
	if (!(*arg->precision))
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

void arg_display_nb(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	arg->len_displayed = ft_atoi(arg->precision);
	if (*(arg->precision) && arg->len_displayed > arg->len_arg)
		arg->nb_zeros = arg->len_displayed - arg->len_arg;
	if (*(arg->width) && arg->len_displayed <= ft_atoi(arg->width))
	{
		if (c_in_s('-', arg->flags) == 1)
		{
			arg->r_pad = ft_atoi(arg->width);
			if (arg->r_pad > arg->len_arg)
				arg->r_pad = arg->r_pad - arg->len_arg - arg->nb_zeros;
			arg->r_pad = arg->r_pad - arg->sign * arg->sign;
		}
		else
		{
			arg->l_pad = ft_atoi(arg->width);
			if (arg->l_pad > arg->len_arg)
				arg->l_pad = arg->l_pad - arg->len_arg - arg->nb_zeros;
			arg->l_pad = arg->l_pad - arg->sign * arg->sign;
		}
	}
}

char *convert_s(t_arg *arg, va_list ap)
{
	char *ret;
	char *pad;
	char *tmp;

	arg->chain = va_arg(ap, char *);
	arg_display_char(arg);
	pad = strset(' ', arg->l_pad + arg->r_pad);
	tmp = ft_substr(arg->chain, 0, arg->len_arg);
	if (arg->r_pad == 0)
		ret = ft_strjoin(pad, tmp);
	else
		ret = ft_strjoin(tmp, pad);
	free(tmp);
	free(pad);
	free_all(arg);
	return (ret);
}

char *convert_c(t_arg *arg, va_list ap)
{
	char *ret;
	char *pad;
	char *tmp;

	arg->chain = ft_str_append(arg->chain, (char )va_arg(ap, int));
	arg_display_char(arg);
	pad = strset(' ', arg->l_pad + arg->r_pad);
	tmp = ft_substr(arg->chain, 0, arg->len_arg);
	if (arg->r_pad == 0)
		ret = ft_strjoin(pad, tmp);
	else
		ret = ft_strjoin(tmp, pad);
	free(tmp);
	free(pad);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

char *make_d_i_u(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->len_arg + arg->r_pad + arg->l_pad + arg->nb_zeros + arg->sign;
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
	handle_d_i_modifiers(arg);
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

char *make_p(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->len_arg + arg->r_pad + arg->l_pad + arg->nb_zeros + 2;
	i = 0;
	j = 0;
	if (!(r = (char *)malloc(sizeof(char) * (t + 1))))
		return (NULL);
	t = arg->l_pad;
	while (t-- > 0)
		r[i++] = ' ';
	r[i++] = '0';
	r[i++] = 'x';
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

void arg_display_p(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	if (c_in_s('-', arg->flags) == 1)
	{
		arg->r_pad = ft_atoi(arg->width);
		if (arg->r_pad > arg->len_arg)
			arg->r_pad = arg->r_pad - arg->len_arg;
		arg->l_pad = 0;
	}
	else
	{
		arg->l_pad = ft_atoi(arg->width);
		if (arg->l_pad > arg->len_arg)
			arg->l_pad = arg->l_pad - arg->len_arg;
		arg->r_pad = 0;
	}
}

char *convert_p(t_arg *arg, va_list ap)
{
	char	*ret;

	arg->chain = ft_itoa_base(va_arg(ap, unsigned long), "0123456789abcdef");
	arg_display_p(arg);
	handle_p_modifiers(arg);
	ret = make_p(arg);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

char *make_x_X(t_arg *arg)
{
	char	*r;
	int		i;
	int		t;
	int		j;

	t = arg->len_arg + arg->r_pad + arg->l_pad + arg->nb_zeros + arg->len_xcomp;
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
	if (arg->type == 'x')
		arg->chain = ft_itoa_base(nb, "0123456789abcdef");
	if (arg->type == 'X')
		arg->chain = ft_itoa_base(nb, "0123456789ABCDEF");
	arg_display_nb(arg);
	handle_x_X_modifiers(arg);
	ret = make_x_X(arg);
	free(arg->chain);
	free_all(arg);
	return (ret);
}

char *convert_percent(t_arg *arg)
{
	char			*ret;

	ret = ft_strdup("%%");
	free_all(arg);
	return (ret);
}

void check_arg(va_list ap, t_arg *arg)
{
	char *tmp;

	if (c_in_s('*', arg->width) ==  1)
	{
		free(arg->width);
		tmp = ft_itoa((va_arg(ap, int)));
		arg->width = ft_strdup(tmp);
		free(tmp);
	}
	if (c_in_s('*', arg->precision) ==  1)
	{
		free(arg->precision);
		tmp = ft_itoa(va_arg(ap, int));
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



void read_fmt(char *fmt, t_config *config, va_list ap)
{
	int	i;
	char *print;
	t_arg *arg;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			if (!(arg = (t_arg *)malloc(sizeof(t_arg))))
				return ;
			initiate_arg(arg);
			core_parsing(fmt, &i, arg, config);
			print = preparing_ret(ap, arg);
			ft_putstr_fd(print, 1);
			free(print);
			free(arg);
		}
		else
			ft_putchar_fd(fmt[i], 1);
		i++;
	}
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	t_config *config;

	if (!(config = (t_config *)malloc(sizeof(t_config))))
		return (-1);
	va_start(ap, fmt);
	initiate_config(config);
	read_fmt((char *)fmt, config, ap);
	va_end(ap);
	free(config);
	return (0);
}

/*int main()
{
	int i;
	int j;
	char *s = "hello";

	i = 0;
	j = 0;*/
	//ft_printf("ft_printf result : ");
	//ft_printf("simple %-10.*s \n", 1 * 2, "LOLZ");
	//ft_printf("simple %-10.*s test %-*c\n", 1 * 2, "LOLZ", '\n', 'L');
	//ft_printf("\nPrintf result    : ");
	//printf("simple %-10.*s test %-*c\n", 1 * 2, "LOLZ", '\n', 'L');
	/*ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.5d' test \n", -10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.12d' test\n", -10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%010d' test\n", -10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '% 0-4d' test\n", -10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.5d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.12d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%010d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.2d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%+10.2d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%+10.5d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%+10.12d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%+10d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%+-10d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '% -10d' test\n", 10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '% -10d' test\n", -10);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%d' test\n", INT_MIN);*/
	/*ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.5u' test\n", 9);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.12u' test\n", 9);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%010u' test\n", 9);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%10.2u' test\n", 9);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%-10u' test\n", 9);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%u' test\n", 9);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%u' test\n", UINT_MAX);*/
/*	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %0#10x\n", 11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %#.5x\n", 11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %#10.5x\n", 11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %#10x\n", 11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %0#10x\n", -11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %#.5x\n", -11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %#10.5x\n", -11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %#10x\n", -11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %-#10x\n", -11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %-#10x\n", 11);
	ft_printf("%d -- ", ++i);
        ft_printf("ceci est une  phrase avec un x : %-#10x\n", INT_MIN);*/
    //ft_printf("ceci est une  phrase avec un x : %-#10% %d%\n", 2);
    //ft_printf("ceci est une  phrase avec un x : %%\n");
	/*ft_printf("%d -- ", ++i);
	ft_printf("simple '%020p' test\n", &s);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%20p' test\n", &s);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%-20p' test\n", &s);
	ft_printf("%d -- ", ++i);
	ft_printf("simple '%-*p' test\n", 20, &s);

	printf("<------------------------------------>\n");*/

/*
	printf("%d -- ", ++j);
	printf("simple '%10.5d' test\n", -10);
	printf("%d -- ", ++j);
	printf("simple '%10.12d' test\n", -10);
	printf("%d -- ", ++j);
	printf("simple '%010d' test\n", -10);
	printf("%d -- ", ++j);
	printf("simple '% 0-4d' test\n", -10);
	printf("%d -- ", ++j);
	printf("simple '%10.5d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%10.12d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%010d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%10.2d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%+10.2d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%+10.5d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%+10.12d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%+10d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '%+-10d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '% -10d' test\n", 10);
	printf("%d -- ", ++j);
	printf("simple '% -10d' test\n", -10);
	printf("%d -- ", ++j);
	printf("simple '%d' test\n", INT_MIN);*/
	/*printf("%d -- ", ++j);
	printf("simple '%10.5u' test\n", 9);
	printf("%d -- ", ++j);
	printf("simple '%10.12u' test\n", 9);
	printf("%d -- ", ++j);
	printf("simple '%010u' test\n", 9);
	printf("%d -- ", ++j);
	printf("simple '%10.2u' test\n", 9);
	printf("%d -- ", ++j);
	printf("simple '%-10u' test\n", 9);
	printf("%d -- ", ++j);
	printf("simple '%u' test\n", 9);
	printf("%d -- ", ++j);
	printf("simple '%u' test\n", UINT_MAX);*/
	/*printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %0#10x\n", 11);
	printf("%d -- ", ++j);
	printf("ceci est une  phrase avec un x : %#.5x\n", 11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %#10.5x\n", 11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %#10x\n", 11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %0#10x\n", -11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %#.5x\n", -11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %#10.5x\n", -11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %#10x\n", -11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %-#10x\n", -11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %-#10x\n", 11);
	printf("%d -- ", ++j);
    printf("ceci est une  phrase avec un x : %-#10x\n", INT_MIN);*/
/*	printf("%d -- ", ++j);
	printf("simple '%020p' test\n", &s);
	printf("%d -- ", ++j);
	printf("simple '%20p' test\n", &s);
	printf("%d -- ", ++j);
	printf("simple '%-20p' test\n", &s);
	printf("%d -- ", ++j);
	printf("simple '%-*p' test\n", 20, &s);
	return (0);
}*/

