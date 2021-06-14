#include "push_swap.h"

int     ft_cmp(t_number *n1, t_number *n2)
{
    return(n1->number - n2->number);
}

void    ft_indexmaker(t_number *n1, int counter)
{
    n1->index = counter + 1;
}

t_group    *ft_create_group(int max, int min)
{
    t_group *group;

    group = ft_calloc(1, sizeof(group));
    group->max = max;
    group->min = min;
    group->mid = (max - min) / 2 + min;
    return (group);
}

void   ft_makelems(t_env *anb, int argc, char **args)
{
    int         i;
    t_number    *number;
    t_group     *group;
    t_list      *sorted_list;

    i = 1;
    sorted_list = 0;
    group = ft_create_group(argc - 1, 1);
    while (i < argc)
    {
        number = ft_calloc(1, sizeof(t_number));
        number->number = ft_atoi(args[i]);
        number->group = group;
        ft_lstadd_back_content(&anb->st_a, number);
        ft_lstadd_content_by_cond(&sorted_list, number,(int (*)(void *, void *))ft_cmp);
        i++;
    }
    ft_lstiteri(sorted_list,(void (*)(void *, int))ft_indexmaker);
    ft_lstclear(&sorted_list, NULL);
}

void ft_show_number(t_number *num)
{
    printf("value %d index %d\n", num->number, num->index);
}
int     main(int  argc, char **argv)
{
    t_env anb;

    ft_bzero(&anb, sizeof(anb));
    ft_makelems(&anb, argc, argv);
    ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
}