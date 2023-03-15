cmake_minimum_required(VERSION 3.2)
set(PROJECT_NAME Calculator)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_PREFIX_PATH $ENV{QTDIR})

include_directories(include)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS forms)
#qt_wrap_ui(MyUi test_form.ui)


add_executable(${PROJECT_NAME}
   src/main.cpp
   src/MainApplication.cpp
   src/MyButton.cpp
   src/Solver.cpp
   include/MainApplication.h
   include/MyButton.h
   include/Solver.h
   forms/test_form.ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
