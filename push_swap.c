#include "push_swap.h"

void	ft_sort_top(t_env *env)
{
	t_number	*n;
	t_number	*nextn;

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
	t_number	*n;
	t_number	*nextn;

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

int	ft_isnum(char *str)
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

void	ft_validation(char **argv)
{
	int	i;
	int	j;
	int	num;
	int	counter;

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
		if (!ft_isnum(argv[i]) || counter == 2)
		{
			write(1, "Error\n", 7);
			exit(0);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_env	anb;

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
		ft_addnewgroup(anb.st_a);
	}
	ft_free(&anb);
	ft_bzero(&anb, sizeof(anb));
	return (0);
}
