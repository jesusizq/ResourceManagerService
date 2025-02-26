set(LIBRARY_NAME "Loaders")
set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/BaseLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/FileLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/HttpLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BundleLoader.cpp"
)

set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/BaseLoader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/FileLoader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/HttpLoader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BundleLoader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/LoaderTypes.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/LoaderFactory.h"
)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE
    Action
    ContentType
)