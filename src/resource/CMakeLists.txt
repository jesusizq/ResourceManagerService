set(LIBRARY_NAME "Resource")
set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Resource.cpp"
)

set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Resource.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Metadata.h"
)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PUBLIC
    ContentType
) 
