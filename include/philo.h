/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:10:12 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/25 23:48:47 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
// Standard Library Includes
#include <stdlib.h>
#include <stdio.h> //printf
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h> //memset

// POSIX Threads Library
#include <pthread.h>

//for get_time 
#include <sys/time.h>


typedef struct s_philo
{
    unsigned int	id;
    pthread_t 		theread_id;		
    pthread_mutex_t	rigth_fork;
	pthread_mutex_t	left_fork;
    unsigned int 	time_last_meal;
    unsigned int	meals_eaten;
    t_info 			*table; // TODO tirar?
} t_philo;

typedef struct s_info
{
	unsigned int	start_time;
	unsigned int	nbr_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_of_meals;
	unsigned int			died;  // ou passar para int;
	unsigned int			all_eaten;
	t_philo					*philos;
	pthread_mutex_t			*forks;
}               t_info;

//utils.c
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_atoi(const char *nptr);

//my_logs.c
size_t my_getime(void);
#endif