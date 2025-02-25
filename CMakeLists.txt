cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME ResourceManagerService)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
message(STATUS "Project: ${PROJECT_NAME} 1.0.0")

add_subdirectory(src)
add_subdirectory(app)

# Set a default install prefix if not specified
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Installation directory" FORCE)
endif()

# INSTALL TARGETS
install(TARGETS ${PROJECT_NAME} DESTINATION bin)