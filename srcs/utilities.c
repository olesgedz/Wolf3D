#include "wolf3d.h"

int			ft_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}