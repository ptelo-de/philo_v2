/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:10:12 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/12/03 11:04:36 by ptelo-de         ###   ########.fr       */
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
    pthread_mutex_t		*fork_one;
	pthread_mutex_t		*fork_two;
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
	t_philo			*philos;
	pthread_mutex_t	*forks; // mesmo numero que philos
	int				Discontinue;
	pthread_t		monitor_id;
	pthread_mutex_t	checker;
}               t_info;

//utils.c
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_atoi(const char *nptr);
int	ft_usleep(size_t millisec);
void	free_table(t_info	*table);
size_t my_getime(void);


//init.c
int init_table(int argc, t_info *table, char *argv[]);
int forks_init(t_info *table);
int create_philos(t_info    *table);
int init_thread(t_info *table);

//routines.c
void    *philo_routine(void	*arg);
void    *monitor_routine(void	*arg);
void	my_log(char *str, int  idx, t_info *table);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int is_Discontinue(t_info *table);

//main.c
int check_args(int argc, char *argv[]);
#endif