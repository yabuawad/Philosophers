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

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((i < n && s1[i] == s2[i]) && s1[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

 long getrealtime()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return((tv.tv_usec / 1000) + tv.tv_sec * 1000);
}

void zzz(int time_to_sleep)
{
	long	initial_time;

	initial_time = getrealtime();
	while((getrealtime() - initial_time) < time_to_sleep)
		usleep(600);
}


void freeall(t_prop *prop)
{
	free(prop->philo);
	destroy_mutexes(prop);
}
