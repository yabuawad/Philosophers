#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

int input_check(char **argv)
{
    int i;
    int x;
    
    i = 1;
    while(argv[i])
    {
        x = 0;
        while(argv[i][x])
        {
            if(!ft_isdigit(argv[i][x]) || ft_atoi(argv[i]) == 0)
            {
                printf("Error\n");
                return 0;
            }
            x++;
        }
        i++;
    }
    return 1;
}
