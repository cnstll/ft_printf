#include <stdio.h>
#include "ft_printf.h"

void parse_precision(char *s, int *i, t_arg *arg)
{
	if (s[*i] == '.')
		while (ft_isdigit(s[++(*i)]) || s[*i] == '*')
			arg->precision = ft_str_append(arg->precision, s[*i]);
}

void core_parsing(char *s, int *i, t_arg *arg, t_config *config)
{
			while (char_in_str((s[++(*i)]), config->flags) == 1)
				if (!char_in_str(s[*i], arg->flags))
					arg->flags = ft_str_append(arg->flags, s[*i]);
			parse_precision(s, i, arg);
			while (ft_isdigit(s[*i]) || s[*i] == '*')
				arg->width = ft_str_append(arg->width, s[(*i)++]);
			parse_precision(s, i, arg);
			if (char_in_str((s[*i]), config->types) == 1)
					arg->type = s[*i];
}

char *convert_s(va_list ap, t_arg *arg)
{
	int	len_ap;
	int l_pad;
	int r_pad;
	int len_displayed;
	char *ret;
	char *s;
	char *pad;
	char *tmp;

	r_pad = (char_in_str('-', arg->flags) == 1) ? ft_atoi(arg->width) : 0;
	l_pad = (char_in_str('-', arg->flags) == 0) ? ft_atoi(arg->width) : 0;
	len_displayed = ft_atoi(arg->precision);
	s = va_arg(ap, char *);
	len_ap = ft_strlen(s);
	if (len_displayed < len_ap)
		len_ap = len_displayed;
	l_pad = (l_pad > len_ap) ? l_pad - len_ap : 0;
	r_pad = (r_pad > len_ap) ? r_pad - len_ap : 0;
	pad = strset(' ', l_pad + r_pad);
	//printf("padding size = %d -- pad = %s\n", l_pad + r_pad, pad);
	tmp = (len_displayed < len_ap) ft_substr(s , 0, len_ap);
	ret = (r_pad == 0) ? ft_strjoin(pad, tmp) : ft_strjoin(tmp, pad);
	free(pad);
	free(tmp);
	return (ret);
}


char *preparing_ret(va_list ap, t_arg *arg, t_config *config)
{
	return (convert_s(ap, arg));
}

void read_fmt(char *s, t_arg *arg, t_config *config, va_list ap)
{
	int	i;
	char *print;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			initiate_arg(arg);
			core_parsing(s, &i, arg, config);
			print = preparing_ret(ap, arg, config);
			ft_putstr_fd(print, 1);
		}
		else
			ft_putchar_fd(s[i], 1);
		i++;
	}
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	t_arg *arg1;
	t_config *config;

	arg1 = malloc(sizeof(t_arg));
	config = malloc(sizeof(t_config));
	va_start(ap, fmt);
	initiate_config(config);
	read_fmt((char *)fmt, arg1, config, ap);
	va_end(ap);
	//printf("flags = '%s' -- width = '%s' -- precision = '%s' -- type = '%c'\n", arg1->flags, arg1->width, arg1->precision, arg1->type);
	//printf("config - %s\n", config->types);
	free(arg1);
	free(config);
	return (0);
}

int main()
{
	ft_printf("simple %-.2s test \n", "LOLZ");
	return (0);
}

