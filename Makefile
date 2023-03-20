# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lizhang <lizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/05 15:23:40 by lizhang       #+#    #+#                  ##
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I ${INCLDIR} 
RM			= rm -f
LIB_PATH	= ./libft/libft.a
MLX_PATH	= ./MLX42/build/libmlx42.a
INCLDIR 	= incl
OBJDIR		= obj
SRCDIR		= src
MLX_FLAG		= -Iinclude -lglfw -ldl -lm  #-lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
FILES			= main.c read_input.c error_messages.c\
			ft_space_split.c parse_utils.c import_textures.c get_player.c \
			get_map.c test_inputs.c parse_color.c boundary_test.c clean_parsing.c\
			keystroke.c keystroke_calc.c dda.c rays_calc.c draw_map.c\
			draw_scene.c rays_utils.c scene_utils.c draw_main.c exe_utils.c

OBJ			= $(FILES:%.c=$(OBJDIR)/%.o)
SRC			= ${FILES:%.c=${SRCDIR}/%.c}			


all:		$(NAME)

$(NAME):	$(OBJ) $(LIB_PATH) $(MLX_PATH)
				$(CC) $(CFLAGS) $(OBJ) $(LIB_PATH)  $(MLX_PATH) $(MLX_FLAG) -o $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
			$(CC) -c $(CFLAGS) -o $@ $<

$(LIB_PATH):
		$(MAKE) WITBON=1 -C libft

$(MLX_PATH):
		cmake -S MLX42 -B ./MLX42/build 
				$(MAKE) -C ./MLX42/build 
$(OBJ) : | $(OBJDIR)

$(OBJDIR) :
	mkdir $@
clean:
			$(RM) -R $(OBJDIR) && cd libft && make clean && $(RM) -rf ../build

fclean:		clean 
			$(RM) $(NAME) && cd libft && make fclean

re:			fclean $(NAME)				

.PHONY:		make all clean fclean re
