# Cub3D

## **Description**
This grafichal project introduce to game developement and ray-casting, mimicking a famous old 3D game *Wolfenstein 3D*<br>
It was made by [@squidtyper](https://github.com/squidtyper/squidtyper) (in charge of the parsing) and [@greedymelon](https://github.com/greedymelon/greedymelon) (in charge of the execution)

# **RULES**
*The map has to respect this set of rules:*
- The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.
- The map must be closed/surrounded by walls, if not the program must return
an error.
- Except for the map content, each type of element can be separated by one or
more empty line(s).
- Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
- Except for the map, each type of information from an element can be separated
by one or more space(s).
- The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map
- Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), 
followed by all specific informations for each object in a strict order such as :<br>
∗ North texture:<br>
NO ./path_to_the_north_texture<br>
· identifier: NO<br>
· path to the north texure<br>
∗ South texture:<br>
SO ./path_to_the_south_texture<br>
· identifier: SO<br>
· path to the south texure<br>
∗ West texture:<br>
WE ./path_to_the_west_texture<br>
· identifier: WE<br>
· path to the west texure<br>
∗ East texture:<br>
EA ./path_to_the_east_texture<br>
· identifier: EA<br>
· path to the east texure<br>
∗ Floor color:<br>
F 220,100,0<br>
· identifier: F<br>
· R,G,B colors in range [0,255]: 0, 255, 255<br>
∗ Ceiling color:<br>
C 225,30,0<br>
· identifier: C<br>
· R,G,B colors in range [0,255]: 0, 255, 255<br>
- If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message

*the program:*
-The management of your window must remain smooth: changing to another window, minimizing, etc.
- Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West).
-Your program must be able to set the floor and ceiling colors to two different ones.
-The program displays the image in a window
-The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
-The W, A, S, and D keys must allow you to move the point of view through
the maze.
-Pressing ESC must close the window and quit the program cleanly.
-Clicking on the red cross on the window’s frame must close the window and
quit the program cleanly.

## **How to run**
First we need to install the grafical libirary
library and step to install it are listed here 
https://github.com/codam-coding-college/MLX42

clone this repository in your computer and open it
```
git clone https://github.com/Squidtyper/Cub3D.git; cd Cub3D
```
then ```make``` the program
run
```./cub3D``` with a map in the folder map:

exemple
```./cub3D /map/scene_normal.cub```

for the bonus part
```make bonus```

run
```./cub3D_bonus``` with a map in the folder map:

exemple
```./cub3D_bonus /map/scene_bonus.cub```

## **Challenges**
