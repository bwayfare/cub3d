cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)
#SET(CMAKE_C_FLAGS "-Wall -Werror -Wextra")
#SET(CMAKE_CTEST_ARGUMENTS "/home/bwayfare/C_Project/cub3D/map1.cub")
#SET(CMAKE_C_FLAGS "-g ")

#add_executable(lvl2_ft_printf main.c)
file(GLOB SOURCE_FILES srcs/*.c include/*.h libft/*.c libft/*.h get_next_line/*.c get_next_line/*.h -lXext -lX11 -lm -lz -lbsd ./mlx/libmlx.a)
#set(VAR srcs/*.c include/*.h libft/*.c libft/*.h get_next_line/*.c get_next_line/*.h)
#set(VAR1 -lXext -lX11 -lm -lz -lbsd ./mlx/libmlx.a -o)

add_executable(cub3D ${SOURCE_FILES})
#add_executable(cub3D ${VAR} ${VAR1})

#gcc -g *.c ./libft/libft.a ./minilibx/libmlx.a -framework OpenGL -framework Appkit
#gcc libft/*.c get_next_line/*.c srcs/*.c -lXext -lX11 -lm -lz -lbsd ./mlx/libmlx.a -o cube3d
#gcc libft/*.c get_next_line/*.c srcs/*.c -lXext -lX11 -lm -lz -lbsd ./mlx/libmlx.a -o cube3d
