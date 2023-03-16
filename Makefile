# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lizhang <lizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/05 15:23:40 by lizhang       #+#    #+#                  #

#                                                                              #
# **************************************************************************** #

NAME		= game
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -D BUFFER_SIZE=1 -fsanitize=address
RM			= rm -f
INCLUDE		= -I include \
			-ICub3D.h -Ilglfw -Ilibft -IMLX42/include

SRC			= main.c read_input.c error_messages.c\
			ft_space_split.c parse_utils.c import_textures.c get_player.c \
			get_map.c test_inputs.c parse_color.c boundary_test.c clean_parsing.c\
			keystroke.c keystroke_calc.c dda.c rays_calc.c draw_map.c\
			draw_scene.c rays_utils.c scene_utils.c draw_main.c \
				$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

OBJ			= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
				$(MAKE) WITBON=1 -C libft
				$(RM) -rf ./MLX42/build
				cmake -S MLX42 -B ./MLX42/build
				cd MLX42/build && make
				$(CC) $(CFLAGS) $(OBJ) libft/libft.a  MLX42/build/libmlx42.a -I include -lglfw \
				-L "/Users/$(USER)/.brew/opt/glfw/lib/"\
				-o $(NAME)

%.o:%.c
			$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<

clean:
			$(RM) $(OBJ) && cd libft && make clean && cd ../MLX42/build && make clean && $(RM) -r ../build

fclean:		clean 
			$(RM) $(NAME) && cd libft && make WITBON=1 fclean
#there is no fclean in MLX42

re:			fclean $(NAME)

.PHONY:		make all clean fclean re so bonus
