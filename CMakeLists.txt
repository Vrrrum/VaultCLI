cmake_minimum_required(VERSION 4.4)
project(passwordManager)

set(CMAKE_CXX_STANDARD 23)

add_executable(passwordManager main.cpp)

include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v7.0.3
)
FetchContent_MakeAvailable(ftxui)

target_link_libraries(passwordManager PRIVATE
        ftxui::ftxui
)