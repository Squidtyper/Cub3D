#include "cube3D.h"
#include "../MLX42/include/MLX42/MLX42.h"

char	map[5][9]= {
{	'1','1','1','1','1','1','1','1', '\0'},
{	'1','D','0','0','D','0','0','1', '\0'},
{	'1','0','0','0','1','D','1','1', '\0'},
{	'1','0','0','0','N','0','0','1', '\0'},
{	'1','1','1','1','1','1','1','1', '\0'}
};

t_input *st_parser(void)
{
	t_input *input;
	
	input = malloc(sizeof(t_input));
	input->map_height = 5;
	input->map_width = 8;
	input->a_player= 3.1415926535;
	input->c_color= 0x2cd22cff;
	input->f_color = 0xfcd22cff;
	input->player_x = 3;
	input->player_y = 3;
	input->textures = NULL;
	input->map_points = (char **)malloc(sizeof (char *) * 5);
	for(int i = 0; i < 5; i++)
	{
		input->map_points[i] = ft_strdup(map[i]);
	}

	ft_lstadd_back(&(input->textures), ft_lstnew((void *)mlx_load_png("./textures/wool_colored_light_blue.png")));
	ft_lstadd_back(&(input->textures), ft_lstnew((void *)mlx_load_png("./textures/wool_colored_lime.png")));
	ft_lstadd_back(&(input->textures), ft_lstnew((void *)mlx_load_png("./textures/wool_colored_red.png")));
	ft_lstadd_back(&(input->textures), ft_lstnew((void *)mlx_load_png("./textures/wool_colored_yellow.png")));
	ft_lstadd_back(&(input->textures), ft_lstnew((void *)mlx_load_png("./textures/sponge.png")));
	return (input);
}


int	main(void)
{
	t_input	*input;

	input = st_parser();
	execution(input);
	clean_input(input);
	return (EXIT_SUCCESS);
}
