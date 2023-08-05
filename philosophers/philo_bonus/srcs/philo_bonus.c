#include "philo_bonus.h"

int main(int argc, char **argv)
{
    t_data  data;

    memset(&data, 0, sizeof(data));
    destroy_sem(&data);
    parsing(argc, argv, &data);
    data.all_finish = 0;
    data.die = 0;
    execute(&data);
}