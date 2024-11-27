/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:36:55 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/27 20:52:39 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    safe_fork_lock(t_philo *philo)
{
    if (philo->id % 2 != 0)
    {
        pthread_mutex_lock(&philo->fork_one);
        pthread_mutex_lock(&philo->fork_two);
    }
    else
    {
        usleep(1000);
        pthread_mutex_lock(&philo->fork_two);
        pthread_mutex_lock(&philo->fork_one);
    }
    
}

void safe_fork_unlock(t_philo *philo)
{

    if (philo->id % 2 != 0)
    {
        pthread_mutex_unlock(&philo->fork_one);
        pthread_mutex_unlock(&philo->fork_two);
        printf("%d %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
    }
    else
    {
        thread_mutex_unlock(&philo->fork_two);
        pthread_mutex_unlock(&philo->fork_one);
        printf("%d %d has taken a fork\n", my_getime() - philo->table->start_time, philo->id);
    }
    
}

void    *philo_routine(t_philo *philo)
{
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
        printf("%d %d is eating\n", my_getime() - philo->table->start_time, philo->id);
        philo->time_last_meal = my_getime() - philo->table->start_time - philo->time_last_meal;
        ft_usleep(philo->table->time_to_eat);
        philo->meals_eaten++;
        safe_fork_unlock(philo);
        printf("%d %d is sleeping\n", my_getime() - philo->table->start_time, philo->id);
        ft_usleep(philo->table->time_to_sleep);
        printf("%d %d is thinking\n", my_getime() - philo->table->start_time, philo->id);
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
void    *monitor_routine(t_info *table) //check with margarida
{
    int i;
    int all_eaten;

    all_eaten = 0;
    while (!table->Discontinue)
    {
        i = 0;
        pthread_mutex_lock(&table->checker);
        while (i < table->nbr_philos)
        {
            if (table->philos[i].time_last_meal >= table->time_to_die)
            {
                table->Discontinue = 1;
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
