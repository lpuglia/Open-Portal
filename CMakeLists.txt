cmake_minimum_required(VERSION 2.8)

project(open_portal)

file(GLOB op_src
    "src/*.cpp"
)

add_executable(open_portal ${op_src}) 

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ./include ./CML)

target_link_libraries(open_portal ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} -lfreeimage)

