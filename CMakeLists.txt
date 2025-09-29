CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(mdparser CXX)
message("project name is automaically set as: ${PROJECT_NAME}")

set(PROJECT_VERSION 1.0.0)

add_executable(main src/index.cpp)
target_include_directories(main PUBLIC include/)
target_link_libraries(main PRIVATE lexer parser generator helper)
target_compile_features(main PRIVATE cxx_std_23)

add_library(helper OBJECT src/tools/helper.cpp)
target_include_directories(helper PUBLIC src/tools/)
target_link_libraries(helper PUBLIC token)

add_library(generator STATIC src/generator.cpp)
target_include_directories(generator PUBLIC include/)
target_link_libraries(generator PUBLIC token)
target_link_libraries(generator PRIVATE helper)

add_library(parser STATIC include/parser.hpp src/parser.cpp)
target_include_directories(parser PUBLIC include/)
target_link_libraries(parser PUBLIC helper lexer)

add_library(lexer OBJECT include/lexer.hpp src/lexer.cpp)
target_include_directories(lexer PUBLIC include/)
target_link_libraries(lexer PUBLIC token helper)

add_library(token INTERFACE include/models/token.hpp)
target_include_directories(token INTERFACE include/models)

MESSAGE(STATUS "--------------------------------------------")
MESSAGE(STATUS "Info :")
MESSAGE(STATUS "  Project Name = ${PROJECT_NAME}")
MESSAGE(STATUS "  Version =     ${PROJECT_VERSION}")
MESSAGE(STATUS "  CMAKE_VERSION =        ${CMAKE_VERSION}")
MESSAGE(STATUS "  CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "  CMAKE_BUILD_TYPE =     ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "  CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "  PCL_VERSION =          ${PCL_VERSION}")
message(STATUS "  OpenCV_VERSION =    ${OpenCV_VERSION}")