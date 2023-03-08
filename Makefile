CC = gcc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

NAME = game

MLX = libmlx42.a

# LIB_PATH = ./libft/libft.a

FILES = main.c \
dda.c \
rayscast.c\
keystroke.c \
keystroke2.c

OBJ = ${FILES:%.c=%.o}

all : ${NAME}

 ${NAME} :  ${MLX} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${MLX} -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o ${NAME} 

${OBJ} : ${FILES}
	${CC} ${CFLAGS} -c ${FILES} 

${MLX} :
	make -C ./MLX42/build; cp ./MLX42/build/libmlx42.a .

re :	fclean all

clean :
	${RM} ${OBJ} ${MLX}; make clean -C ./MLX42/build

bonus :
	$(MAKE) all ISBONUS=1

fclean : clean
	${RM} ${NAME} 

.PHONY: all clean fclean re
