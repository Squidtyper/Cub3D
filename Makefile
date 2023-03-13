# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lizhang <lizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/05 15:23:40 by lizhang       #+#    #+#                  #
#    Updated: 2023/03/13 14:13:42 by dmonfrin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= game
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -D BUFFER_SIZE=1 -fsanitize=address
RM			= rm -f
INCLUDE		= -I include \
			-ICub3D.h -Ilglfw -Ilibft -IMLX42/include


SRC			= main.c keystroke.c keystroke2.c dda.c rayscast.c map_draw.c\
			scene.c read_input.c error_messages.c ray_utility.c cube3d_draw.c\
			ft_space_split.c parse_utils.c import_textures.c get_player.c \
			get_map.c test_inputs.c \
				$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

OBJ			= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
				$(MAKE) WITBON=1 -C libft
				make -C ./MLX42/build
				$(CC) $(CFLAGS) $(OBJ) libft/libft.a  MLX42/build/libmlx42.a -I include -lglfw \
				-L "/Users/$(USER)/.brew/opt/glfw/lib/"\
				-o $(NAME)

%.o:%.c
			$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<

clean:
			$(RM) $(OBJ) && make clean -C ./MLX42/build && cd libft && $(MAKE) clean make clean -C ./MLX42/build

fclean:		clean 
			$(RM) $(NAME) && cd libft && $(MAKE) fclean

re:			fclean $(NAME)

.PHONY:		make all clean fclean re so bonus