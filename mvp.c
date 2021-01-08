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
			while (char_in_str((s[++(*i)]), config->flags) == 1)
				if (!char_in_str(s[*i], arg->flags))
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
			if (char_in_str((s[*i]), config->types) == 1)
					arg->type = s[*i];
}

void arg_display(t_arg *arg)
{
	arg->len_arg = ft_strlen(arg->chain);
	arg->len_displayed = ft_atoi(arg->precision);
	if (*(arg->precision) && arg->len_displayed < arg->len_arg)
		arg->len_arg = arg->len_displayed;
	if (char_in_str('-', arg->flags) == 1)
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
	//printf("> arg->len_arg : %d\n> arg->len_displayed : %d\n", arg->len_arg, arg->len_displayed);
}

char *convert_s(t_arg *arg, va_list ap)
{
	char *ret;
	char *pad;
	char *tmp;

	arg->chain = va_arg(ap, char *);
	arg_display(arg);
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
	arg_display(arg);
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

void check_arg(va_list ap, t_arg *arg, t_config *config)
{
	char *tmp;

	if (char_in_str('*', arg->width) ==  1)
	{
		free(arg->width);
		tmp = ft_itoa((va_arg(ap, int)));
		arg->width = ft_strdup(tmp);
		free(tmp);
	}
	if (char_in_str('*', arg->precision) ==  1)
	{
		free(arg->precision);
		tmp = ft_itoa(va_arg(ap, int));
		arg->precision = ft_strdup(tmp);
		free(tmp);
	}
}

char *preparing_ret(va_list ap, t_arg *arg, t_config *config)
{
		check_arg(ap, arg, config);
		if (arg->type == 'c')
			return (convert_c(arg, ap));
		else if (arg->type == 's')
			return (convert_s(arg, ap));
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
			//printf("\n> arg->flags : %s\n> arg->width : %s\n", arg->flags, arg->width);
			//printf("> arg->type : %c\n", arg->type);
			print = preparing_ret(ap, arg, config);
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

int main()
{
	ft_printf("ft_printf result : ");
	ft_printf("simple %-10.*s \n", 1 * 2, "LOLZ");
	//ft_printf("simple %-10.*s test %-*c\n", 1 * 2, "LOLZ", '\n', 'L');
	//ft_printf("\nPrintf result    : ");
	//printf("simple %-10.*s test %-*c\n", 1 * 2, "LOLZ", '\n', 'L');
	return (0);
}

