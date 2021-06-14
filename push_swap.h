#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "./libft/libft.h"


typedef struct  s_env
{
    t_list *group;
    t_list *st_a;
    t_list *st_b;
}               t_env;

typedef struct  s_group
{
    int max;
    int min;
    int mid;
}               t_group;

typedef struct s_number
{
    int number;
    int index;
    t_group *group;
}               t_number;

#endif