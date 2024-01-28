project(OpencvExample)

cmake_minimum_required(VERSION 3.16)

add_compile_options(-std=c++17)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(tugascv src/tugassatu.cpp)
target_link_libraries(tugascv ${OpenCV_LIBS})

add_executable(tugascvd src/tugasdua.cpp)
target_link_libraries(tugascvd ${OpenCV_LIBS})

add_executable(tugascvt src/tugastiga.cpp)
target_link_libraries(tugascvt ${OpenCV_LIBS})