# Project metadata
set(PROJECT_NAME "p101_search")
set(PROJECT_VERSION "0.0.1")
set(PROJECT_DESCRIPTION "Portable table, tree, list, and queue search operations")
set(PROJECT_LANGUAGE "C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(STANDARD_FLAGS
        -D_POSIX_C_SOURCE=200809L
        -D_XOPEN_SOURCE=700
        -Werror
)
set(DARWIN_STANDARD_FLAGS -D_DARWIN_C_SOURCE)
set(LINUX_STANDARD_FLAGS -D_GNU_SOURCE)
set(BSD_STANDARD_FLAGS -D_BSD_SOURCE -D__BSD_VISIBLE)

set(LIBRARY_TARGETS p101_search)
set(p101_search_SOURCES
        src/search.c
)
set(p101_search_HEADERS
        include/p101_search/search.h
)
set(p101_search_LINK_LIBRARIES
        p101_error
        p101_env
        p101_c
)

