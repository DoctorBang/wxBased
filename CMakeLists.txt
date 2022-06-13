cmake_minimum_required(VERSION 3.20)
project(BasedApp)

find_package(wxWidgets REQUIRED core base)
include(${wxWidgets_USE_FILE})

add_executable(BasedApp App.cpp BasedWindow.cpp)
target_link_libraries(BasedApp ${wxWidgets_LIBRARIES})
target_precompile_headers(BasedApp PUBLIC pch.h)