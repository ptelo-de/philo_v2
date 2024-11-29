/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:36:55 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/29 16:09:14 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    safe_fork_lock(t_philo *philo)
{
    if (philo->id % 2 != 0)
    {
        pthread_mutex_lock(philo->fork_one);
        pthread_mutex_lock(philo->fork_two);
    }
    else
    {
        usleep(1000);
        pthread_mutex_lock(philo->fork_two);
        pthread_mutex_lock(philo->fork_one);
    }
    
}

void safe_fork_unlock(t_philo *philo)
{

    if (philo->id % 2 != 0)
    {
        pthread_mutex_unlock(philo->fork_one);
        pthread_mutex_unlock(philo->fork_two);
        printf("%lu %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
    }
    else
    {
        pthread_mutex_unlock(philo->fork_two);
        pthread_mutex_unlock(philo->fork_one);
        printf("%lu %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
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
        safe_fork_lock(philo);
        printf("%lu %d is eating\n", my_getime() - philo->table->start_time, philo->id);
        philo->time_last_meal = my_getime() - philo->table->start_time - philo->time_last_meal;
        ft_usleep(philo->table->time_to_eat);
        philo->meals_eaten++;
        safe_fork_unlock(philo);
        printf("%lu %d is sleeping\n", my_getime() - philo->table->start_time, philo->id);
        ft_usleep(philo->table->time_to_sleep);
        printf("%lu %d is thinking\n", my_getime() - philo->table->start_time, philo->id);
        ft_usleep(philo->table->time_to_think);
    }
    return (NULL);
}
int check_all_eaten(int all_eaten, t_info *table)
{
        if (all_eaten == table->nbr_of_meals)
        {
            table->Discontinue = 1;
            pthread_mutex_unlock(&table->checker);
            return (1);
        }
        return (0);
    
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
        pthread_mutex_lock(&table->checker);
        i = 0;
        while (i < table->nbr_philos)
        {
            if (table->philos[i].time_last_meal >= table->time_to_die)
            {
                table->Discontinue = 1;
                printf("%lu %d died\n", my_getime() - table->start_time, table->philos[i].id);
                pthread_mutex_unlock(&table->checker);
                return (NULL);
            }
            if (table->philos[i].meals_eaten == table->nbr_of_meals)
                all_eaten++;
            i++;  
        }  
        if (check_all_eaten(all_eaten, table))
            return (NULL);
        pthread_mutex_unlock(&table->checker);
    }
    return (NULL);
}
