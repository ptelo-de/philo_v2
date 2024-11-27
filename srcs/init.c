/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:24:20 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/27 19:30:01 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void fork_assigment(t_info *table)
{
	int i;

	table->philos[0].fork_one = &table->forks[0];
	table->philos[0].fork_two = &table->forks[table->nbr_philos - 1];
	table->philos[table->nbr_philos - 1].fork_one = &table->forks[i - 1];
	table->philos[table->nbr_philos - 1].fork_two = &table->forks[i];
	i = 1;
	while (i < (table->nbr_philos - 1))
	{
		if (i % 2 != 0)
		{
			table->philos[i].fork_one = &table->forks[i - 1];
			table->philos[i].fork_two = &table->forks[i];
		}
		else
		{
			table->philos[i].fork_one = &table->forks[i];
			table->philos[i].fork_two = &table->forks[i - 1];
		}
        i++;
    }
}
int init_table(int argc, t_info *table, char *argv[])
{
    table->nbr_philos = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (check_args(argc, argv) ||table->nbr_philos <=0 || table->time_to_die <=0
       || table->time_to_eat < 0 || table->time_to_sleep < 0)
        return (1);
    if (argc == 6)
    {
        table->nbr_of_meals = ft_atoi(argv[5]);
        if (table->nbr_of_meals <= 0)
            return (1);
    }
    if (table->nbr_philos == 1)
    {
        table->start_time = my_getime();
        ft_usleep(table->time_to_die);
        printf("0 1 has taken a fork\n%d 1 died\n", table->time_to_die);
        return (1);
    }
    if ( table->nbr_philos % 2 != 0)
        table->time_to_think = 0.2 * (2 *table->time_to_eat);
    else if (table->time_to_eat > table->time_to_sleep)
        table->time_to_think = table->time_to_eat - table->time_to_sleep;
    return (0);
}

int forks_init(t_info *table)
{
	int i;

    table->forks = (pthread_mutex_t *)ft_calloc(table->nbr_philos, sizeof(pthread_mutex_t));
    if(!table->forks)
    {
        return (1);   
    }
	i = 0;
	while (i < table->nbr_philos)
	{
	    if (pthread_mutex_init(&table->forks[i], NULL) != 0) 
			return (1);
		i++;
    }
    if (pthread_mutex_init(&table->checker, NULL) != 0) 
			return (1);
	return (0);
}

int create_philos(t_info    *table)
{
    int id;

    table->philos = ft_calloc(table->nbr_philos, sizeof(t_philo));
    if (!table->philos)
        return (1);
    id = 1;
    while (id <= table->nbr_philos)
    {
        table->philos[id - 1].id = id;
        printf("id :%d\n", table->philos[id - 1].id);
        table->philos[id -1].meals_eaten = 0;
        printf(" meals_eaten: %d\n", table->philos[id - 1].meals_eaten);
        table->philos[id - 1].table = table;
        printf(" table: %p\n", table->philos[id - 1].table);
        printf(" orignila table: %p\n", table);
        table->philos[id - 1].theread_id = 0;
        printf(" thread id: %lu\n", table->philos[id - 1].theread_id);
        table->philos[id - 1].time_last_meal = 0;
        printf(" time last meal: %d\n", table->philos[id - 1].time_last_meal);
        id++;
        
    }
    fork_assigment(table);
    return (0);
}

int init_thread(t_info *table)
{
    int i;

    i = 0;
    //pthread_mutex_lock(table->checker);
    table->start_time = my_getime();
    while (i < table->nbr_philos)
    {
        if (pthread_create(&table->philos[i].theread_id, NULL, &philo_routine, (void *)(&table->philos[i])) != 0) 
        {
            free_table(table);
            return (1);
        }
        i++;
    }
    
    if (pthread_create(&table->monitor_id, NULL, &monitor_routine, (void *)table) != 0)
    {
        free_table(table);
        return (1);
    }
    //pthread_mutex_lock(table->checker);
    while (i < table->nbr_philos)
    {
		if(pthread_join(table->philos[i].theread_id, NULL) != 0) //evita zombie threads
            return (1);
        i++;
    }
    if (pthread_join(table->monitor_id, NULL) != 0)
        return (1);
    return (0);
}
