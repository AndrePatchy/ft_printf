# include "ft_printf.h"

// check format 

int ft_check_format(va_list ptr, const char c)
{
    int ret;

    ret = 0;
    if (c == 'c')
        ret += ft_print_char(va_arg(ptr, int));
    else if (c == 's')
        ret += ft_print_str(va_arg(ptr, char *));
    else if (c == 'p')
        ret += ft_print_ptr(va_arg(ptr, unsigned long long));
    else if (c == 'd' || c == 'i')
        ret += ft_print_nbr(va_arg(ptr, int));
    else if (c == 'u')
        ret += ft_print_unsigned_dec(va_arg(ptr, unsigned int));
	else if (c == 'x' || c == 'X')
		ret += ft_print_hex(va_arg(ptr, unsigned int), c);
	else if (c == '%')
		ret += ft_print_percentage();
    return (ret);
}

// %%

int	ft_print_percentage(void)
{
	write(1, "%", 1);
	return (1);
}

// %x

int	ft_print_hex(unsigned int n, const char c)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		ft_hex(n, c);
	return (ft_len_hex(n));
}

void ft_hex(unsigned int n, const char c)
{
	if (n >= 16)
	{
		ft_hex(n / 16, c);
		ft_hex(n % 16, c);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((n - 10 + 'a'), 1);
			if (c == 'X')
				ft_putchar_fd((n - 10 + 'A'), 1);
		}
	}
}

int	ft_len_hex(unsigned int n)
{
	int	l;

	l = 0;
	while (n != 0)
	{
		l++;
		n = n / 16;
	}
	return (l);
}

// %u
// The representation of negative numbers is done using the most significant bit as a sign bit
// So, n is implicitly converted to an unsigned int.
// For a 32-bit unsigned int, the max value is 2^32 = 4294967295, which we have to subtract by n.
// If n = -9, -9 gets converted to 4294967287

int	ft_print_unsigned_dec(unsigned int n)
{
	int	ret;
	char	*number;

	ret = 0;
	if (n == 0)
		ret += write(1, "0", 1);
	else
	{
		number = ft_unsigned_itoa(n);
		ret += ft_print_str(number);
		free(number);
	}
	return (ret);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char	*number;
	int	l;

	l = ft_nbr_len(n);
	number = (char *)malloc((l + 1) * sizeof(char));
	if (!number)
		return (0);
	number[l] = '\0';
	while (n != 0)
	{
		number[l - 1] = n % 10 + 48;
		n = n / 10;
		l--;
	}
	return (number);
}

int	ft_nbr_len(unsigned int n)
{
	int	l;

	l = 0;
	while (n != 0)
	{
		l++;
		n = n / 10;
	}
	return (l);
}

// %d or %i

int ft_print_nbr(int n)
{
    int length;
    char    *num;

    length = 0;
    num = ft_itoa(n);
    length = ft_print_str(num);
    free(num);
    return (length);
}

// %p

int ft_print_ptr(unsigned long long ptr)
{
    int ret;

    ret = 0;
    ret += write(1, "0x", 2);
    if (ptr == 0)
        ret += write(1, "0", 1);
    else
    {
        ft_put_ptr(ptr);
        ret += ft_ptr_len(ptr);
    }
    return (ret);
}

int ft_ptr_len(uintptr_t nbr)
{
    int length;

    length = 0;
    while (nbr != 0)
    {
        length++;
        nbr = nbr /16;
    }
    return (length);
}

void ft_put_ptr(uintptr_t nbr)
{
    if (nbr >= 16)
    {
        ft_put_ptr(nbr / 16);
        ft_put_ptr(nbr % 16);
    }
    else
    {
        if (nbr <= 9)
            ft_putchar_fd((nbr + '0'), 1);
        else
            ft_putchar_fd((nbr - 10 + 'a'), 1);
    }
}

// %s

void    ft_put_str(char *string)
{
    int i;

    i = 0;
    while (string[i])
    {
        write(1, &string[i], 1);
        i++;
    }
}

int     ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int ft_print_str(char *string)
{
    int i;

    i = 0;
    if (string == NULL)
    {
        ft_put_str("(null)");
        return (6);
    }
    while (string[i])
    {
        write(1, &string[i], 1);
        i++;
    }
    return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// itoa

int	ft_length(int n)
{
	int	len;

	len = 0;
	if (n<= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ft_fillingz(int len, int offset, int n, char *result)
{
	while (len > offset)
	{
		result[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	int		offset;
	int		len;
	char	*result;

	offset = 0;
	len = ft_length(n);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n == -2147483648)
	{
		result[0] = '-';
		result[1] = '2';
		n = 147483648;
		offset = 2;	
	}
	if (n < 0)
	{
		result[0] = '-';
		offset = 1;
		n = -n;
	}
	ft_fillingz(len, offset, n, result);
	result[len] = '\0';
	return (result);
}