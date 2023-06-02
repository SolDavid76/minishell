#include "exec.h"

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int fd, int n)
{
	unsigned int	x;

	if (n < 0)
	{
		x = -n;
		ft_putchar_fd(fd, '-');
	}
	else
		x = n;
	if (x > 9)
	{
		ft_putnbr_fd(fd, x / 10);
		x = x % 10;
	}
	ft_putchar_fd(fd, x + '0');
}

int	intlen(long int x)
{
	size_t	res;

	res = 1;
	if (x < 0)
	{
		x = -x;
		res++;
	}
	while (x > 9)
	{
		x /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int x)
{
	char		*res;
	int			start;
	int			len;
	long int	nb;

	nb = x;
	len = intlen(nb);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	start = 0;
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
		start++;
	}
	while (len >= start)
	{
		res[len--] = ((nb % 10) + 48);
		nb /= 10;
	}
	return (res);
}
