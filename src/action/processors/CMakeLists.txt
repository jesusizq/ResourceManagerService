set(LIBRARY_NAME "Processors")
set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/ImageDecoder.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Decompressor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/JsonParser.cpp"
)

set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/ImageDecoder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Decompressor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/JsonParser.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ProcessorFactory.h"
)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE
    Action
    Logger
    ContentType
)