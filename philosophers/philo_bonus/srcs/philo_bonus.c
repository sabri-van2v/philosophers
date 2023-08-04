#include "philo_bonus.h"

int main(int argc, char **argv)
{
    t_data  data;
    //int     finish_value;

    destroy_sem(&data);
    parsing(argc, argv, &data);
    //finish_value = 0;
    data.all_finish = 0;
    data.die = 0;
    execute(&data);
}