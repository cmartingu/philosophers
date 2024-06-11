# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_datos
{
	pthread_mutex_t	m_last_eat_time;
	pthread_mutex_t	m_can_start;
	pthread_mutex_t	m_write;
	size_t			ini_time;
	int				times_to_eat;
	int				num_philo;
	int				can_start;
	size_t			ttd;
	int				tte;
	size_t				tts;
	int				end;
}	t_datos;

typedef struct s_philo
{
	pthread_mutex_t	m_times_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	size_t			last_eat;
	int				times_eaten;
	t_datos			*data;
}	t_philo;

typedef struct s_general
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*hilos;
	t_datos			*data;
	pthread_t		hilo_aux;
}	t_general;

void	ini_general(t_general *all, char *argv[], int argc);
size_t	get_time_in_ms(void);
void	usleep_functional(size_t time);
int		parse_args(char *argv[]);

#endif