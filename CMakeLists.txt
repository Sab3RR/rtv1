cmake_minimum_required(VERSION 3.13)
project(rtv1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit ")
file(GLOB LIB libft/*.c)
file(GLOB INCLIB libft/*.h)

add_executable(rtv1 main.c inc/rtv1.h ${LIB} ${INCLIB} init.c ft_free.c pr.c add_ob.c obj.c render.c helper.c obj_form.c light.c helper2.c hud.c cone.c)