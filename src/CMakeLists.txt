include_directories(.)
include_directories(v8)
include_directories(v8/include)

add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(pdf)
add_subdirectory(ppapi)
add_subdirectory(printing)
add_subdirectory(third_party/pdfium)
add_subdirectory(v8)

add_executable(dep_check dep_check.c)
target_link_libraries(dep_check pdf)
