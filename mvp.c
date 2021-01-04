#include <stdio.h>
#include "/home/nath/42projects/libft/libft.h"

typedef struct	s_arg
{
	char	*flags; //"-+0 #"
	char	type; //"cspdiuxX%"
	char	*width; //number or *
	char	*precision; //number or *
}				t_arg;

char *ft_str_append(char *s, char c)
{
	unsigned int	len;
	char	*r;
	int		i;

	len = ft_strlen(s);
	i = 0;
	//printf("Entered str_append with *s = %s\n", *s);
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

int	already_in_str(char c, char *s)
{
	while(*s)
		if (c == *s++)
			return (1);
	return (0);
}

int	is_flag(char c)
{
	//printf("Entered is_flag\n");
	static char	*flags = "-+0 #";
	int		i;

	i = 0;
	while (flags[i])
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_type(char c)
{
	//printf("Entered is_type\n");
	static char	*types = "cspdiuxX%";
	while (*types)
	{
		if (c == *types++)
			return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

void ft_initiate_arg(t_arg *arg)
{
	arg->flags = "";
	arg->type = 0;
	arg->width = "";
	arg->precision = "";
}

void parse_precision(char *s, int *i, t_arg **arg)
{
	if (s[*i] == '.')
		while (ft_isdigit(s[++*i]) || s[*i] == '*')
			(*arg)->precision = ft_str_append((*arg)->precision, s[*i]);
}

void parser(char *s, t_arg *arg)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			ft_initiate_arg(arg);
			i++;
			while (is_flag((s[i])) == 1)
			{
				if (!already_in_str(s[i], arg->flags))
					arg->flags = ft_str_append(arg->flags, s[i]);
				i++;
			}
			parse_precision(s, &i, &arg);
			while (ft_isdigit(s[i]) || s[i] == '*')
				arg->width = ft_str_append(arg->width, s[i++]);
			parse_precision(s, &i, &arg);
			if (is_type((s[i])) == 1)
					arg->type = s[i];
		}
		i++;
	}
}

int main()
{
	t_arg arg1;

	char *str_to_print = "simple %-+000000000 #20c test ";

	//printf("flags %s -- types %s\n", flags, types);
	parser(str_to_print, &arg1);
	printf("flags = '%s' -- width = '%s' -- precision = '%s'					-- type = '%c'\n", arg1.flags, arg1.width, arg1.precision, arg1.type);
	free(arg1.flags);
	//printf("result append str = %s",ft_str_append("Hell",'o'));
}

