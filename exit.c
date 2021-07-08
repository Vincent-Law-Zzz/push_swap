#include "push_swap.h"

void	ft_free(t_env *env)
{
	if (env->st_a)
		ft_lstclear(&env->st_a, free);
	if (env->st_b)
		ft_lstclear(&env->st_b, free);
	if (env->group)
		ft_lstclear(&env->group, free);
}

void	ft_exit(t_env *env)
{
	ft_free(env);
	write(1, "Error\n", 7);
	exit(0);
}

int	ft_cmp(t_number *n1, t_number *n2)
{
	return (n1->number - n2->number);
}
