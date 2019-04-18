cmake_minimum_required(VERSION 3.13)
project(rtv1 C)

set(CMAKE_C_STANDARD 99)
file(GLOB LIB libft/*.c)
file(GLOB INCLIB libft/*.h)

add_executable(rtv1 main.c inc/rtv1.h ${LIB} ${INCLIB} init.c ft_free.c)