/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:36:55 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/30 19:02:11 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    eat_with_forks(t_philo *philo)
{
    if (philo->id % 2 != 0)
    {
        usleep(1000);
        pthread_mutex_lock(philo->fork_one);
        my_log("has taken a fork", philo->id, philo->table);
        pthread_mutex_lock(philo->fork_two);
        my_log("has taken a fork", philo->id, philo->table);
    }
    else
    {
        usleep(1000);
        pthread_mutex_lock(philo->fork_two);
        my_log("has taken a fork", philo->id, philo->table);
        pthread_mutex_lock(philo->fork_one);
        my_log("has taken a fork", philo->id, philo->table);
    }
    my_log("is eating", philo->id, philo->table);
    pthread_mutex_lock(&philo->table->checker);
    philo->time_last_meal = my_getime() - philo->table->start_time - philo->time_last_meal;
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->table->checker);
    ft_usleep(philo->table->time_to_eat);
    if (philo->id % 2 != 0)
    {
        pthread_mutex_unlock(philo->fork_two);
        pthread_mutex_unlock(philo->fork_one);
    }
    else
    {
        pthread_mutex_unlock(philo->fork_one);
        pthread_mutex_unlock(philo->fork_two);
    }
    
}

void    *philo_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    
    while (1)
    {
        pthread_mutex_lock(&philo->table->checker);
        if (philo->table->Discontinue)
        {
            pthread_mutex_unlock(&philo->table->checker);
            return(NULL);
        }
        pthread_mutex_unlock(&philo->table->checker);
        eat_with_forks(philo);
        my_log("is sleeping", philo->id, philo->table);
        ft_usleep(philo->table->time_to_sleep);
        my_log("is thinking", philo->id, philo->table);
        ft_usleep(philo->table->time_to_think);
    }
    return (NULL);
}

void    *monitor_routine(void *arg) //check with margarida
{
    int i;
    int all_eaten;
    t_info *table;

    table = (t_info *)arg;

    all_eaten = 0;
    pthread_mutex_lock(&table->checker);
    while (!table->Discontinue)
    {
        i = 0;
        while (i < table->nbr_philos)
        {
            if (table->philos[i].time_last_meal >= table->time_to_die)
            {
                table->Discontinue = 1;
                my_log("died", table->philos[i].id, table);
                pthread_mutex_unlock(&table->checker);
                return (NULL);
            }
            if (table->philos[i].meals_eaten == table->nbr_of_meals)
                all_eaten++;
            i++;  
        }  
        if (all_eaten == table->nbr_of_meals)
        {
            table->Discontinue = 1;
            pthread_mutex_unlock(&table->checker);
            return (NULL);
        }
    }
    pthread_mutex_unlock(&table->checker);
    return (NULL);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i] && i < (n - 1) && (s1[i] || s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void my_log(char *str, int  idx, t_info *table)
{
    if (!ft_strncmp("died", str, 4))
    {
        printf("%lu %d died\n", my_getime() - table->start_time, idx);
        return;
    }
    pthread_mutex_lock(&table->checker);
    if (!table->Discontinue)
        printf("%lu %d %s\n", my_getime() - table->start_time, idx, str);
    pthread_mutex_unlock(&table->checker);
    
}