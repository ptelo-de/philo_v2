/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:17:23 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/26 21:07:35 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    initial_clean(t_info *table)
{
    table->all_eaten = 0;
    table->died = 0;
    table->forks = NULL;
    table->nbr_of_meals = 0;
    table->nbr_philos = 0;
    table->philos = NULL;
    table->start_time = 0;
    table->time_to_die = 0;
    table->time_to_eat = 0;
    table->time_to_sleep = 0;
    table->time_to_think = 0;
}
int main(int argc, char *argv[])
{
    t_info table; 

    (void)argv;
    
    if (argc != 5 && argc != 6)
    {
        printf("ERROR: Wrong number of elements\n");
        return (0); // nao podes usar o exit
    }
    initial_clean(&table);
    init_table(argc, &table, argv);
        // check_args;
            // check num of philos
    // init_forks
    // philos = malloc(sizeof(table->philo) * table->nbr_of_philos)); // dentro do create philos
    // create_philos(table);   
    // init_threads
    //
    // 
    return (0);
}

// void init_table(t)

/*
! [] IMPORTANTE 
	TODO [] exit is not allowed;

[] clean initial memory;
[] check args (parsing) and // TODO init table
	[] check nbr of philos
		[]if nbr_philos == 1
			[] wait x time and return(0); // ?
	[] atoi for only positiv numbers;
	[] check args > 0 && time_to_sleep >= 0;
	// [] //TODO (get_my_time) ?

// [] init_table
// 	[] start_time ? //! (get_my_time)
//  	[] args na info 
[] init_forks
	[] malloc sizof(mutex) * nrb_philos;
	[] mutex forks;

philos = malloc(sizeof(table->philo) * table->nbr_of_philos));
[] create philos
	[] while()
		[]id = idx
		[] info 0;
		[] pointer p a table;
		[]  fork assigment - mutex rigth and left 
			[] pointer p r_fork; - forks[nbr_philos] + 1;
			[] pointer p l_fork; - forks[nbr_philos] - 1;
				[]if philo = 0
					l_forke[nrb_philos];

[] init_threads; //? dentro do create philos? //
	[] create routine function // in philo_utils.c
		? What each philosopher has to do ? In which order ?
		[] consider:
			[] impar and par
			[] mutex lock
			[] mutex unlock 
	   [] eat
	   		[] time_last_meal  init when we starts to eat
			[] meals_eaten++;
	   [] sleep
	   [] think /shit
	   [] repeat
	   [] printf
	[] start_time ? //! (get_my_time)
	[] while(nrb_philos)
		[] p_thread_create(table->philo->theread_id, routine, table->philo);
	[] p_thread_create(..., death_routine)

[]check_is_alive - death_routine)
	[] new routine 
	[] mutex lock;
	[] mutex unlock;
	[] call a function to check if the philo eat 
	[] call to check is alive;

[] ? - threads_join
	[]while(nbr_philos);
		[]p_thread_join();

[] free
	[] philo
		[] r_fokr;
		[] l_fork;
		[] *info;
	[] distroy mustex forks;
*/


/* 
Core concepts:
    [] process vs threads
    [] threads
    [] mutexes
    bonus:
        [] semaphores

[] #define ERROR_MSG;
[] structs:
    [] philo  - principal
        [x] id (number);
        [x] p_thread 
        [x] mutex rigth_fork;
        [x] mutex left_fork;
        [x] time_last_meal;
        [x] meals_eaten ?;
        [x] t_info *info;
         
    [X] info
        [x] start_time;
        [x] nbr_of_philo;
        [x] time_to_die;
        [x] time_to_eat;
        [x] time_to_sleep;
        [x] nbr_of_meals;
        [x] int died ?;
        [x] int all_eaten ;
        
*/