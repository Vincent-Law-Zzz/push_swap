#include "push_swap.h"


void	ft_content_free(void *content)
{
	if (content)
	{
		free(content);
	}
}

void ft_free(t_env * env)
{
	if (env->st_a)
		ft_lstclear(&env->st_a, ft_content_free);
	if (env->st_b)
		ft_lstclear(&env->st_a, ft_content_free);
	if (env->group)
		ft_lstclear(&env->group, ft_content_free);
	free (env->st_a);
	free (env->st_b);
	free (env->group);
}

int     ft_cmp(t_number *n1, t_number *n2)
{
    return(n1->number - n2->number);
}

void    ft_indexmaker(t_number *n1, int counter)
{
    n1->index = counter + 1;
}

t_group    *ft_create_group(t_env *env, int max, int min)
{
    t_group *group;

    group = ft_calloc(1, sizeof(t_group));
    group->max = max;
    group->min = min;
    group->mid = (max - min) / 2 + min;
	ft_lstadd_back_content(&env->group,group);
    return (group);
}

void   ft_makelems(t_env *anb, int argc, char **args)
{
    int         i;
    t_number    *number;
    t_list      *sorted_list;

    i = 1;
    sorted_list = 0;
	anb->group = ft_lstnew((void *)ft_create_group(anb, argc - 1, 1));
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
    ft_lstclear(&sorted_list,NULL);
}

void ft_show_number(t_number *num)
{
    printf("value %d index %d\n", num->number, num->index);
}

void	ft_pop(t_env *env)
{
	t_list * lst;

	lst = env->st_a;
	while(lst && ((t_number *)lst->content)->group != NULL)
		lst = lst->next;
	while(lst && lst->next && ((t_number *)lst->content)->group == NULL)
	{
		if (((t_number *)lst->next->content)->group != NULL && ((t_number *)lst->next->content)->index == env->nexti)
			((t_number *)lst->next->content)->group = NULL;
		lst = lst->next;
	}y
	while (((t_number *)(ft_lstlast(env->st_a))->content)->group != NULL && env->nexti > 1)
			ft_rra(env);
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
	while (i <= (tmp->mid - tmp->min) && tmp == tmpn && tmp && tmpn)
	{
		index = ((t_number *)env->st_a->content)->index;
		tmp = (t_group *)((t_number *)((t_list *)env->st_a)->content)->group;
		tmpn = (t_group *)((t_number *)((t_list *)env->st_a->next)->content)->group;
		if (index <= tmp->mid)
		{
			ft_pb(env);
			i++;
		}
		else
			ft_ra(env);		
	}
}

int		ft_calcmin(t_list *stack)
{
	t_list *tmp;
	int min;

	min = ((t_number *)stack->content)->index;
	tmp = stack;
	while(tmp)
	{
		if (min > ((t_number *)tmp->content)->index)
			min = ((t_number *)tmp->content)->index;
		tmp = tmp->next;
	}
	return (min);
}

int		ft_calcmax(t_list *stack)
{
	t_list *tmp;
	int max;

	max = ((t_number *)stack->content)->index;
	tmp = stack;
	while(tmp)
	{
		if (max < ((t_number *)tmp->content)->index)
			max = ((t_number *)tmp->content)->index;
		tmp = tmp->next;
	}
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
	if(!g)
		return ;
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
	else
		ft_rb(env);
}

void	ft_btoa(t_env *env)
{
	t_group *tmp;
	t_number *number;
	int	count;

	while (env->st_b)
	{
		tmp = ft_create_group(env, ft_calcmax(env->st_b), ft_calcmin(env->st_b));
		count = ft_lstsize(env->st_b);
		while ( count-- && env->st_b)
		{
			number = ((t_number *)env->st_b->content);
			if (number->index > tmp->mid)
			{
				number->group = tmp;
				ft_pa(env);
			}
			else if (number->index <= tmp->mid)
				ft_sort(env, number->index);
		}
	}
}

int	ft_condition(t_env *env,t_list *tmp1, t_list *tmp2)
{
	if (tmp1 && ((t_number *)tmp1->content)->index == env->nexti)
		return (1);
	else if (tmp1->next && ((t_number *)tmp1->next->content)->index == env->nexti)
		return (2);
	else if (tmp2 && ((t_number *)tmp2->content)->index == env->nexti)
		return (3);
	else if (tmp2 && tmp2->next && ((t_number *)tmp2->next->content)->index == env->nexti)
		return (4);
	return (0);
}

void	ft_littlsearch(t_env *env,t_list *tmp1, t_list *tmp2)
{
	if (ft_condition(env,tmp1,tmp2) == 1)
		ft_ra(env);
	else if (ft_condition(env,tmp1,tmp2) == 2)
	{
		ft_sa(env);
		ft_ra(env);
	}
	else if (ft_condition(env,tmp1,tmp2) == 3)
	{
		ft_pa(env);
		ft_ra(env);
	}
	else if (ft_condition(env,tmp1,tmp2) == 4)
	{
		ft_sb(env);
		ft_pa(env);
		ft_ra(env);
	}
	else
	{
		ft_pb(env);
		return ;
	}
	env->nexti = env->nexti + 1;
}

void	ft_get_position(t_env *env, t_list *tmp1)
{
	if (((t_number *)tmp1->content)->index == 1)
		ft_ra(env);
	else if (tmp1->next && ((t_number *)tmp1->next->content)->index == 1)
	{
		ft_sa(env);
		ft_ra(env);
	}
	else if (tmp1->next && tmp1->next->next && ((t_number *)tmp1->next->next->content)->index == 1)
	{
		ft_rra(env);
		ft_rra(env);
	}
	else if (tmp1->next && tmp1->next->next->next && ((t_number *)tmp1->next->next->next->content)->index == 1)
		ft_rra(env);
	env->nexti = env->nexti + 1;
}

void	ft_littlsort(t_env *env, int argc)
{
	t_list *tmp1;
	t_list *tmp2;
	int	flag;

	flag = 0;
	tmp1 = env->st_a;
	tmp2 = env->st_b;
	ft_get_position(env, tmp1);
	while (env->nexti < argc)
	{
		tmp1 = env->st_a;
		tmp2 = env->st_b;
		ft_littlsearch(env, tmp1, tmp2);
	}
}

void	ft_sort_top(t_env *env)
{
	t_number *n;
	t_number *nextn;

	n = ((t_number *)(env->st_a->content));
	nextn = ((t_number *)(env->st_a->next->content));
	while (n && nextn && (n->index == env->nexti || nextn->index == env->nexti))
	{
		n = ((t_number *)(env->st_a->content));
		nextn = ((t_number *)(env->st_a->next->content));
		if (n->index == env->nexti)
		{
			((t_number *)(env->st_a->content))->group = NULL;
			env->nexti = env->nexti + 1; 
			ft_ra(env);
		}
		else if (nextn && (nextn->index == env->nexti))
		{
			ft_sa(env);
			((t_number *)(env->st_a->content))->group = NULL;
			env->nexti = env->nexti + 1;
			ft_ra(env);
		}
	}
}

void	ft_comb3(t_env *env)
{
	t_number *n;
	t_number *nextn;

	if (!env->st_a->next)
		return ;
	n = ((t_number *)(env->st_a->content));
	nextn = ((t_number *)(env->st_a->next->content));
	if (n->index == 1 && nextn->index == 3)
	{
		ft_rra(env);
		ft_sa(env);
	}
	else if (n->index == 3 && nextn->index == 1)
		ft_ra(env);
	else if (n->index == 2 && nextn->index == 3)
		ft_rra(env);
	else if (n->index == 3 && nextn->index == 2)
	{
		ft_sa(env);
		ft_rra(env);
	}
	else if (n->index == 2 && nextn->index == 1)
		ft_sa(env);
	env->nexti = 4;
}
int		ft_isnum(char *str)
{
	int	flag;

	flag = 0;
	if (str[0] == '-')
	{
		flag = 1;
		str++;
	}
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}

void ft_validation(char **argv)
{
	int i;
	int j;
	int num;
	int counter;

	i = 1;
	while (argv[i])
	{
		j = 1;
		num = ft_atoi(argv[i]);
		counter = 0;
		while (argv[j])
		{
			if (num == ft_atoi(argv[j]))
				counter++;
			j++;
		}
		if(!ft_isnum(argv[i]) || counter == 2)
		{
			write(1,"Error\n",7);
			exit(0);
		}
		i++;
	}
}

int     main(int  argc, char **argv)
{
    t_env anb;

    ft_bzero(&anb, sizeof(anb));
	anb.nexti = 1;
	ft_validation(argv);
    ft_makelems(&anb, argc, argv);
	if (argc - 1 < 4)
		ft_comb3(&anb);
	else if (argc - 1 < 6 && anb.nexti == 1)
		ft_littlsort(&anb, argc);
	while (anb.nexti < argc - 1)
	{
		ft_atob(&anb);
		ft_pop(&anb);
		ft_btoa(&anb);
		ft_sort_top(&anb);
		ft_addnewgroup(&anb,anb.st_a);
	}
	// printf("next i %d\n", anb.nexti);
	// printf (" %d stack A\n", anb.nexti);
	// ft_lstiter(anb.st_a, (void (*)(void *))ft_show_number);
	ft_free(&anb);
	// getchar();
	return (0);
}

