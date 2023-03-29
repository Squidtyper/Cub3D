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
BNAME		= cub3D_bonus
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I ${INCLDIR} -g -fsanitize=address 
RM			= rm -f
LIB_PATH	= ./libft/libft.a
MLX_PATH	= ./MLX42/build/libmlx42.a
INCLDIR 	= include
OBJDIR		= obj
SRCDIR		= src
BSRCDIR		= bonus_src
MLX_FLAG	= -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
FILES_SHARE	= error_messages.c\
			ft_space_split.c parse_utils.c get_player.c parse_color.c \
			draw_dda.c rays_calc.c draw_map.c \
			rays_utils.c draw_scene_utils.c draw_main.c \
			execution.c read_input.c import_textures.c get_map.c test_inputs.c boundary_test.c \
			clean_parsing.c execution_utils.c 
FILES_MAN	= main.c draw_scene.c keystroke.c keystroke_calc.c
FILES_B		= 	read_input_bonus.c import_textures_bonus.c \
			get_map_bonus.c boundary_test_bonus.c main_bonus.c\
			test_inputs_bonus.c draw_scene_bonus.c\
			keystroke_bonus.c keystroke_calc_bonus.c hook_loop_bonus.c sprite_bonus.c
OBJ			= ${FILES_SHARE:%.c=${OBJDIR}/%.o} ${FILES_MAN:%.c=${OBJDIR}/%.o}
SRC			= ${FILES_SHARE:%.c=${SRCDIR}/%.o}${FILES_MAN:%.c=${SRCDIR}/%.c}
BOBJ		= $(FILES_SHARE:%.c=$(OBJDIR)/%.o) ${FILES_B:%.c=${OBJDIR}/%.o}
BSRC		= ${FILES_SHARE:%.c=${SRCDIR}/%.c} ${FILES_B:%.c=${BSRCDIR}/%.c} 

all:		$(NAME)

$(NAME):	$(OBJ) $(LIB_PATH) $(MLX_PATH)
				$(CC) $(CFLAGS) $(OBJ) $(LIB_PATH)  $(MLX_PATH) $(MLX_FLAG) -o $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
			$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o:$(BSRCDIR)/%.c
			$(CC) -c $(CFLAGS) -o $@ $<

bonus:		$(BNAME)
$(BNAME):	$(BOBJ) $(LIB_PATH) $(MLX_PATH)
				$(CC) $(CFLAGS) $(BOBJ) $(LIB_PATH)  $(MLX_PATH) $(MLX_FLAG) -o $(BNAME)

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
			$(RM) $(NAME) $(BNAME) && cd libft && make fclean

re:			fclean $(NAME)

.PHONY:		make all clean fclean re bonus
