#include "push_swap.h"

// int		ft_exit(int code)
// {
// if (code == 0)
// {

// }
// }

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
	// ((t_number *)tmp->content)->group = new;
	ft_lstadd_back_content(&env->group,new);
	// printf("max %d mid %d min %d\n",new->max, new->mid, new->min);
}

int	ft_shiftcount(t_env *env)
{
	t_list * lst;
	int counter;
	int flag;

	lst = env->st_a;
	flag = 1;
	counter = 0;
	// while (lst->next)
	// {
		while(lst->next && ((t_number *)lst->content)->group)
			lst = lst->next;
		while(lst->next && !((t_number *)lst->content)->group)
		{
			if (((t_number *)lst->next->content)->group && ((t_number *)lst->next->content)->index == env->nexti)
				((t_number *)lst->next->content)->group = NULL;
			lst = lst->next;
		}
		while(lst->next && ((t_number *)lst->content)->group)
		{
			counter++;
			lst = lst->next;
		}
	// 	if (flag == 1)
	// 		if (!((t_number *)lst->content)->group)
	// 			flag = -1;
	// 	if (flag == -1 && ((t_number *)lst->next->content)->group && ((t_number *)lst->next->content)->index == env->nexti)
	// 		((t_number *)lst->next->content)->group = NULL;
	// // 	if (flag == -1)
	// 		if (((t_number *)lst->content)->group)
	// 			flag = 0;
	// 	if (flag == 0)
	// 		counter++;
	// 	lst = lst->next;
	// }
	// printf(" counter , %d\n", counter);
	return counter;
}

void	ft_atob(t_env *env)
{
	t_group *tmp;
	t_group *tmpn;
	int	i;
	int index;

	i = 0;
	tmp = (t_group *)((t_number *)((t_list *)env->st_a)->content)->group;
	tmpn = (t_group *)((t_number *)((t_list *)env->st_a->next)->content)->group;
	index = ((t_number *)env->st_a->content)->index;
	// getchar();
	while (i <= tmp->max && tmp == tmpn)
	{
		if (index <= tmp->mid)
		{
			ft_pb(env);
		}
		else
			ft_ra(env);
		i++;
		index = ((t_number *)env->st_a->content)->index;
		tmp = (t_group *)((t_number *)((t_list *)env->st_a)->content)->group;
		tmpn = (t_group *)((t_number *)((t_list *)env->st_a->next)->content)->group;
	}
		if (index <= tmp->mid)
		{
			ft_pb(env);
		}
		else
			ft_ra(env);
}

int		ft_calcmin(t_list *stack)
{
	t_list *tmp;
	int min;

	min = ((t_group *)((t_number *)stack->content)->group)->max;
	tmp = stack;
	while(tmp->next)
	{
		if (min > ((t_group *)((t_number *)tmp->content)->group)->min)
			min = ((t_group *)((t_number *)tmp->content)->group)->min;
		tmp = tmp->next;
	}
	// printf("min %d \n",min);
	return (min);
}

int		ft_calcmax(t_list *stack)
{
	t_list *tmp;
	int max;

	max = ((t_group *)((t_number *)stack->content)->group)->min;
	tmp = stack;
	while(tmp->next)
	{
		if (max < ((t_group *)((t_number *)tmp->content)->group)->max)
			max = ((t_group *)((t_number *)tmp->content)->group)->max;
		tmp = tmp->next;
	}
	// printf("max %d \n",max);
	return (max);
}

void ft_addnewgroup(t_env __unused *env,t_list *stack)
{
	t_list *tmp;
	t_group *g;
	t_group *nextg;
	int min;

	tmp = stack;
	g = ((t_number *)tmp->content)->group;
	nextg = ((t_number *)tmp->next->content)->group;
	min = g->mid;
	while (((t_number *)tmp->content)->group != NULL && g == nextg)
	{
		g->min = min;
		g->mid = (g->max - g->min)/2 + g->min;
		tmp = tmp->next;
		g = ((t_number *)tmp->content)->group;
		nextg = ((t_number *)tmp->next->content)->group;
	}
	if(!g)
		return ;
	g->min = min;
	g->mid = (g->max - g->min)/2 + g->min;
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
	else if (index < ((t_group *)((t_number *)env->st_b->content)->group)->mid)
		ft_rb(env);
}

void	ft_btoa(t_env *env)
{
	t_group *tmp;
	int index;
	int i;

	i = 0;
	if (!env->st_b)
		return;
	index = ((t_number *)env->st_b->content)->index;
	tmp = ((t_number *)env->st_b->content)->group;
	while (env->st_b->next)
	{
		getchar();
		ft_groupelem(env,env->st_b,ft_create_group(ft_calcmax(env->st_b), ft_calcmin(env->st_b)));
		printf("___________max %d min %d__________\n", ft_calcmax(env->st_b),ft_calcmin(env->st_b));
		tmp = ((t_number *)env->st_b->content)->group;
		i = 1;
		while (i <= tmp->mid && env->st_b->next)
		{
			// printf("index min %d i %d\n", ((t_group *)((t_number *)env->st_b->content)->group)->min, i);
			if (index >= tmp->mid)
			{
				ft_pa(env);
				i++;
			}
			else if (index <= tmp->mid)
				ft_sort(env, index);
			else
				break;
			index = ((t_number *)env->st_b->content)->index;
			printf("index st_a %d\n", index);
			printf (" %d stack A\n", env->nexti);
			ft_lstiter(env->st_a, (void (*)(void *))ft_show_number);
			printf (" %d stack B\n", env->nexti);
			ft_lstiter(env->st_b, (void (*)(void *))ft_show_number);
			printf("index min %d i %d\n", ((t_group *)((t_number *)env->st_b->content)->group)->min, i);
			getchar();
		}
	}
	ft_sort(env, index);
}


void	ft_sort_top(t_env *env)
{
	if (((t_number *)(env->st_a->content))->index == env->nexti)
	{
		((t_number *)(env->st_a->content))->group = NULL;
		env->nexti = env->nexti + 1; 
		ft_ra(env);
	}
	if (((t_number *)(env->st_a->next->content))->index == env->nexti)
	{
		((t_number *)(env->st_a->next->content))->group = NULL;
		env->nexti = env->nexti + 1;
		ft_sa(env);
		ft_ra(env);
	}
}

int     main(int  argc, char **argv)
{
    t_env anb;
	int	i;

    ft_bzero(&anb, sizeof(anb));
	anb.nexti = 1;
    ft_makelems(&anb, argc, argv);
	ft_atob(&anb);
	i = 0;
	while (anb.nexti < argc - 1)
	{
	
		// printf (" %d stack A\n", anb.nexti);
		// ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
		// printf (" %d stack B\n", anb.nexti);
		// ft_lstiter(anb.st_b, (void (*)(void *))ft_show_number);
		// printf("index min %d i %d\n", ((t_group *)((t_number *)anb.st_a->content)->group)->max, i);
		ft_btoa(&anb);
		ft_addnewgroup(&anb,anb.st_a);
		ft_sort_top(&anb);
		ft_atob(&anb);
		i = ft_shiftcount(&anb);
		while (((t_number *)(ft_lstlast(anb.st_a))->content)->group != NULL)
			ft_rra(&anb);
		ft_sort_top(&anb);
	}
	// printf("next i %d\n", anb.nexti);
	// printf (" %d stack A\n", anb.nexti);
	// ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
}

