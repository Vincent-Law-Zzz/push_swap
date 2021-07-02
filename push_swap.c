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

    group = ft_calloc(1, sizeof(t_group));
    group->max = max;
    group->min = min;
    group->mid = (max - min) / 2 + min;
    return (group);
}

void   ft_makelems(t_env *anb, int argc, char **args)
{
    int         i;
    t_number    *number;
    // t_group     *group;
    t_list      *sorted_list;

    i = 1;
    sorted_list = 0;
	anb->group = ft_lstnew((void *)ft_create_group(argc - 1, 1));
    while (i < argc)
    {
        number = ft_calloc(1, sizeof(t_number));
        number->number = ft_atoi(args[i]);
        number->group = anb->group->content;
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

void	ft_groupelem(t_env *env, t_list *stack,t_group *new)
{
	t_list *tmp;

	tmp = stack;
	while (tmp->next)
	{
		if (((t_number *)tmp->content)->group->max == ((t_number *)tmp->next->content)->group->max)
			((t_number *)tmp->content)->group = new;
		else
			break;
		tmp = tmp->next;
	}
	((t_number *)tmp->content)->group = new;
	ft_lstadd_back_content(&env->group,new);
	printf("max %d mid %d min %d\n",new->max, new->mid, new->min);
}

void	ft_atob(t_env *env)
{
	t_group *tmp;
	t_group *tmpn;
	t_group *new;
	int	i;
	int min;
	int index;

	i = 0;
	tmp = (t_group *)((t_number *)((t_list *)env->st_a)->content)->group;
	tmpn = (t_group *)((t_number *)((t_list *)env->st_a->next)->content)->group;
	min = ((t_number *)env->st_a->content)->index;
	index = ((t_number *)env->st_a->content)->index;
	while (i < tmp->max && (tmp->max == tmpn->max))
	{
		if (index <= tmp->mid)
		{
			if (min > index)
				min = index;
			ft_pb(env);
		}
		else
			ft_ra(env);
		i++;
		index = ((t_number *)env->st_a->content)->index;
	}
	new = ft_create_group(tmp->mid, tmp->min);
	printf("new group min %d mid %d max %d\n", new->min,new->mid,new->max);
	ft_groupelem(env, env->st_b, new);
}

void ft_sort(t_env *env, int index)
{
	if (index == env->nexti)
	{
		((t_number *)env->st_b->content)->group = NULL;
		ft_pa(env);
		ft_ra(env);
		env->nexti = env->nexti + 1;
	}
	else if (!env->st_b->next)
		ft_pa(env);
	else
		ft_rb(env);
}

void	ft_btoa(t_env *env)
{
	t_group *tmp;
	t_group *new;
	int min;
	int index;

	tmp = (t_group *)((t_number *)env->st_b->content)->group;
	min = ((t_number *)env->st_b->content)->index;
	index = ((t_number *)env->st_b->content)->index;
	while (env->st_b->next)
	{
		if (index > tmp->mid)
			ft_pa(env);
		else
		{
			if (min > index)
				min = index;
			ft_sort(env,index);
		}
		index = ((t_number *)env->st_b->content)->index;
	}
	ft_sort(env,index);
	new = ft_create_group(tmp->mid, tmp->min);
	printf("new group min %d mid %d max %d\n", new->min,new->mid,new->max);
	ft_groupelem(env, env->st_a, new);
}

// void	ft_move(t_env *env)
// {
// 	t_group *tmp;
// 	t_group *new;
// 	int min;
// 	int index;

// 	tmp = (t_group *)((t_number *)env->st_b->content)->group;
// 	min = ((t_number *)env->st_b->content)->index;
// 	index = ((t_number *)env->st_b->content)->index;
// 	while (env->st_b->next)
// 	{
// 		if (index > tmp->mid)
// 			ft_pa(env);
// 		else
// 			ft_sort(env,index);
// 		if (min > index)
// 				min = index;
// 		index = ((t_number *)env->st_b->content)->index;
// 	}
// 	ft_sort(env,index);
// 	new = ft_create_group(tmp->mid, tmp->min);
// 	printf("new group min %d mid %d max %d\n", new->min,new->mid,new->max);
// 	ft_groupelem(env, env->st_a, new);
// }

int     main(int  argc, char **argv)
{
    t_env anb;

    ft_bzero(&anb, sizeof(anb));
	anb.nexti = 1;
    ft_makelems(&anb, argc, argv);
	ft_atob(&anb);
	printf (" 1 stack A\n");
	ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
	printf (" 1 stack B\n");
	ft_lstiter(anb.st_b, (void (*)(void *))ft_show_number);
	ft_btoa(&anb);
	printf (" 2 stack A\n");
	ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
	printf (" 2 stack B\n");
	ft_lstiter(anb.st_b, (void (*)(void *))ft_show_number);
	ft_atob(&anb);
	printf (" 1 stack A\n");
	ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
	printf (" 1 stack B\n");
	ft_lstiter(anb.st_b, (void (*)(void *))ft_show_number);
	printf(" %d\n", anb.nexti);
}

