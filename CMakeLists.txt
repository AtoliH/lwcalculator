cmake_minimum_required(VERSION 3.24)
project(lwcalculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(lwcalculator main.cpp Parser.cpp Parser.h)

add_subdirectory(lwlib)

target_include_directories(${PROJECT_NAME} PUBLIC
        "lwlib/include")
target_include_directories(${PROJECT_NAME} PUBLIC
        /usr/local/include
        /usr/local/opt/openssl@3/include)
target_link_directories(${PROJECT_NAME} PUBLIC
        /usr/local/lib
        /usr/local/opt/openssl@3/lib)

include(FindOpenCL)
find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${OpenCL_LIBRARIES}
        lwlib
        amqpcpp
        ev
        nlohmann_json::nlohmann_json)
