cmake_minimum_required(VERSION 3.8)
set(SOURCE_CODE samplePwm CACHE NAME "Target object name")

project( ${SOURCE_CODE} CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable( ${SOURCE_CODE} ${SOURCE_CODE}.cpp)
# ライブラリのリンクを指定
target_link_libraries(${SOURCE_CODE} JetsonGPIO)