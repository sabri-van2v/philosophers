#include "philo_bonus.h"

void    close_sem(t_data *data)
{
    sem_close(data->forks);
    sem_close(data->finish);
    sem_close(data->death);
    sem_close(data->checker);
}

void    destroy_sem(t_data *data)
{
    close_sem(data);
    sem_unlink("forks");
    sem_unlink("finish");
    sem_unlink("death");
    sem_unlink("checker");
}
