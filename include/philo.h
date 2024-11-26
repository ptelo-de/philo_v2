/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:10:12 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/26 20:47:19 by ptelo-de         ###   ########.fr       */
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

typedef struct s_info t_info;

typedef struct s_philo
{
    int	id;
    pthread_t 			theread_id;		
    pthread_mutex_t		*rigth_fork;
	pthread_mutex_t		*left_fork;
    int 				time_last_meal;
    int					meals_eaten;
   	t_info 				*table; // TODO tirar ?
} t_philo;

typedef struct s_info
{
	size_t			start_time;
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				nbr_of_meals;
	int				died;  // TODO ou passar para int;
	int				all_eaten;
	t_philo			*philos;
	pthread_mutex_t	*forks; // mesmo numero que philos
}               t_info;

//utils.c
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_atoi(const char *nptr);
int	ft_usleep(size_t millisec);

//my_logs.c
size_t my_getime(void);


//init.c
int init_table(int argc, t_info *table, char *argv[]);
#endif