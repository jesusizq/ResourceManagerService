set(LIBRARY_NAME "Logger")

set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Logger.h")

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
