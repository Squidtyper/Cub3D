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
CFLAGS		= -Wall -Werror -Wextra -I ${INCLDIR} #-fsanitize=address
RM			= rm -f
LIB_PATH	= ./libft/libft.a
MLX_PATH	= ./MLX42/build/libmlx42.a
INCLDIR 	= incl
OBJDIR		= obj
BOBJDIR		= bonus_obj
SRCDIR		= src
BSRCDIR		= bonus_src
MLX_FLAG	= -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
FILES_SHARE	= error_messages.c\
			ft_space_split.c parse_utils.c get_player.c parse_color.c \
			keystroke.c keystroke_calc.c dda.c rays_calc.c draw_map.c \
			draw_scene.c rays_utils.c scene_utils.c draw_main.c 
FILES_MAN	= main.c read_input.c \
			import_textures.c \
			get_map.c test_inputs.c boundary_test.c clean_parsing.c
FILES_B		= main_bonus.c read_input_bonus.c \
			import_textures.c \
			get_map_bonus.c boundary_test.c \
			clean_parsing_bonus.c test_inputs_bonus.c clean_parsing_bonus.c
OBJ			= $(FILES_SHARE:%.c=$(OBJDIR)/%.o) ${FILES_MAN:%.c=${OBJDIR}/%.o}
SRC			= ${FILES_SHARE:%.c=${SRCDIR}/%.c} ${FILES_MAN:%.c=${SRCDIR}/%.c}
BOBJ		= $(FILES_SHARE:%.c=$(BOBJDIR)/%.o) ${FILES_B:%.c=${BOBJDIR}/%.o}
BSRC		= ${FILES_SHARE:%.c=${BSRCDIR}/%.c} ${FILES_B:%.c=${BSRCDIR}/%.c} 


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
