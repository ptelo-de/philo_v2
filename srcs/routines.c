/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:36:55 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/30 16:51:18 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    eat_with_forks(t_philo *philo)
{
    if (philo->id % 2 != 0)
    {
        usleep(1000);
        pthread_mutex_lock(philo->fork_one);
        printf("%lu %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
        pthread_mutex_lock(philo->fork_two);
        printf("%lu %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
    }
    else
    {
        usleep(1000);
        pthread_mutex_lock(philo->fork_two);
        printf("%lu %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
        pthread_mutex_lock(philo->fork_one);
        printf("%lu %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
    }
    printf("%lu %d is eating\n", my_getime() - philo->table->start_time, philo->id);
    philo->time_last_meal = my_getime() - philo->table->start_time - philo->time_last_meal;
    ft_usleep(philo->table->time_to_eat);
    philo->meals_eaten++;
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
        if (philo->table->Discontinue)
        {
            return(NULL);
        }
        eat_with_forks(philo);
        printf("%lu %d is sleeping\n", my_getime() - philo->table->start_time, philo->id);
        ft_usleep(philo->table->time_to_sleep);
        printf("%lu %d is thinking\n", my_getime() - philo->table->start_time, philo->id);
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
    while (!table->Discontinue)
    {
        i = 0;
        while (i < table->nbr_philos)
        {
            if (table->philos[i].time_last_meal >= table->time_to_die)
            {
                table->Discontinue = 1;
                printf("%lu %d died\n", my_getime() - table->start_time, table->philos[i].id);
                return (NULL);
            }
            if (table->philos[i].meals_eaten == table->nbr_of_meals)
                all_eaten++;
            i++;  
        }  
        if (all_eaten == table->nbr_of_meals)
        {
            table->Discontinue = 1;
            return (NULL);
        }
    }
    return (NULL);
}
