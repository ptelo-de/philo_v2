/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:26:28 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/27 16:31:28 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		nb = 10 * nb + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	max;

	max = nmemb * size;
	if (nmemb && size && max / size != nmemb)
		return (NULL);
	array = malloc(max);
	if (!array)
		return (NULL);
	memset(array, 0, max);
	return (array);
}

int	ft_usleep(size_t millisec)
{
	size_t	start;

	start = my_getime();
	while ((my_getime() - start) < millisec) 
		usleep(500);
	return (0);
}

size_t my_getime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	free_table(t_info	*table)
{
    int i;


    if (table->philos)
    {
    	i = 0;
		while (i < table->nbr_philos)
		{
			table->philos[i].fork_one = NULL;
			table->philos[i].fork_two = NULL;
			table->philos[i].table = NULL;
			i++;
		}
        free(table->philos);
        table->philos = NULL;
    }
    i = 0;
    if (table->forks) {
        while (i < table->nbr_philos) {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
        free(table->forks);
        table->forks = NULL;
    }
}