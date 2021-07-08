#include "push_swap.h"

void	ft_rra(t_env *env)
{
	t_list	*tmp;
	t_list	*end;

	if (!env->st_a || !env->st_a->next)
		return ;
	end = env->st_a;
	while (end->next)
	{
		tmp = end;
		end = end->next;
	}
	ft_lstadd_front(&env->st_a, end);
	tmp->next = NULL;
	write (1, "rra\n", 4);
}

void	ft_rrb(t_env *env)
{
	t_list	*tmp;
	t_list	*end;

	if (!env->st_b || !env->st_b->next)
		return ;
	end = env->st_b;
	while (end->next)
	{
		tmp = end;
		end = end->next;
	}
	ft_lstadd_front(&env->st_b, end);
	tmp->next = NULL;
	write (1, "rrb\n", 4);
}

void	ft_rrr(t_env *env)
{
	ft_rra(env);
	ft_rrb(env);
	write(1, "(equiv. to rrr)\n", 17);
}
