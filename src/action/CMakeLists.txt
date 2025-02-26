# Collect all action objects
set(LIBRARY_NAME "Action")

add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} INTERFACE
    Resource
    Logger
)

# Include subdirectories
add_subdirectory(loaders)
add_subdirectory(processors)
