/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:24:20 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/26 19:20:59 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int init_table(int argc, t_info *table, char *argv[])
{
    table->nbr_philos = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);

    if (table->nbr_philos <=0 || table->time_to_die <=0)
        return (-1);
    if (table->time_to_eat < 0 || table->time_to_sleep < 0)
        return (-1);
    if (argc == 6)
    {
        table->nbr_of_meals = ft_atoi(argv[5]);
        if (table->nbr_of_meals <= 0)
            return (-1);
    }
    if (table->nbr_philos == 1)
    {
        table->start_time = my_getime();
        ft_usleep()
    }
}