cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)
#SET(CMAKE_C_FLAGS "-Wall -Werror -Wextra")
SET(CMAKE_CTEST_ARGUMENTS "/home/bwayfare/C_Project/cub3D/map1.cub")

#add_executable(lvl2_ft_printf main.c)
file(GLOB SOURCE_FILES *.c *.h libft/*.c libft/*.h get_next_line/*.c get_next_line/*.h)

add_executable(cub3D ${SOURCE_FILES})