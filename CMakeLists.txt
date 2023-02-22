cmake_minimum_required(VERSION 3.8)
project(interview)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_PREFIX_PATH vcpkg_installed/x64-linux/share)
set(CMAKE_CXX_STANDARD 20)



include_directories(
    inc
    vcpkg_installed/x64-linux/include
 
)

LINK_DIRECTORIES(
    vcpkg_installed/x64-linux/lib
)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.hpp)


add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES})


find_package(GLEW REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(SDL2 CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    )



