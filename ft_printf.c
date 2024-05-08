# include "ft_printf.h"

int ft_printf(const char *string, ...)
{
	va_list	ptr;
	int	i;
	int	ret;
	
	i = 0;
	ret = 0;
	va_start(ptr, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			ret += ft_check_format(ptr, string[i + 1]);
			i++;	
		}
		else
			ret += ft_print_char(string[i]);
		i++;
	}
	va_end(ptr);
	return (ret);
}

int main(void)
{
	ft_printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&");
	printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&");
	return (0);
}