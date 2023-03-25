#include "cube3D.h"

// static void	st_clean_input(t_input *input)
// {
// 	mlx_delete_texture(input->NO_tex);
// 	mlx_delete_texture(input->SO_tex);
// 	mlx_delete_texture(input->WE_tex);
// 	mlx_delete_texture(input->EA_tex);
// 	free(input);
// }

int	main(int ac, char **av)
{
	t_input	*input;

	input = parse(ac, av);
	execution(input);
	clean_input(input);
	return (EXIT_SUCCESS);
}
