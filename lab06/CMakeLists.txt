cmake_minimum_required(VERSION 3.10.2)
project(aur)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("./include")

set(AUR_SOURCES include/scene/scene.hpp
                include/objects/object.hpp
                include/objects/camera.hpp
                include/objects/mesh.hpp
                include/geometries/vertex.hpp
                include/geometries/geometry.hpp
                include/geometries/es2_geometry.hpp
                include/geometries/geometry_generators.hpp
                include/materials/material.hpp
                include/materials/constant_material.hpp
                include/materials/es2_constant_material.hpp
                include/materials/phong_material.hpp
                include/materials/es2_phong_material.hpp
                include/lights/ambient_light.hpp
                include/lights/light.hpp
                include/lights/directional_light.hpp
                include/lights/point_light.hpp
                include/lights/spot_light.hpp
                include/textures/texture.hpp
                include/textures/es2_texture.hpp
                include/renderer/renderer.hpp
                include/renderer/es2_renderer.hpp
                include/renderer/shader.hpp
                include/renderer/es2_shader.hpp
                include/window/window.hpp
                include/window/sdl_window.hpp
                include/utilities/utilities.hpp
                include/aur.hpp)

add_executable(window_test ${AUR_SOURCES} tests/window_test.cpp)
add_executable(triagle_test ${AUR_SOURCES} tests/triangle_test.cpp)
add_executable(scene_graph_test ${AUR_SOURCES} tests/scene_graph_test.cpp)
add_executable(other_geometries_test ${AUR_SOURCES} tests/other_geometries_test.cpp)
add_executable(lighting_test ${AUR_SOURCES} tests/lighting_test.cpp)

target_link_libraries(window_test ${CONAN_LIBS})
target_link_libraries(triagle_test ${CONAN_LIBS})
target_link_libraries(scene_graph_test ${CONAN_LIBS})
target_link_libraries(other_geometries_test ${CONAN_LIBS})
target_link_libraries(lighting_test ${CONAN_LIBS})

