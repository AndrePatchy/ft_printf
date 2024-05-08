# ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_printf(const char *, ...);
int	ft_print_char(int c);
int ft_check_format(va_list ptr, const char c);
int ft_print_str(char *string);
int ft_print_char(int c);
void    ft_put_str(char *string);
int ft_print_ptr(unsigned long long ptr);
void ft_put_ptr(uintptr_t nbr);
int ft_ptr_len(uintptr_t nbr);
void	ft_putchar_fd(char c, int fd);
int ft_print_nbr(int n);
int	ft_length(int n);
void	ft_fillingz(int len, int offset, int n, char *result);
char	*ft_itoa(int n);
int	ft_print_unsigned_dec(unsigned int n);
char	*ft_unsigned_itoa(unsigned int n);
int	ft_nbr_len(unsigned int n);
int	ft_print_hex(unsigned int n, const char c);
void ft_hex(unsigned int n, const char c);
int	ft_print_percentage(void);
int	ft_len_hex(unsigned int n);

# endif