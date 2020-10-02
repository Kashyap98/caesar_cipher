cmake_minimum_required(VERSION 3.16.3)
project (decrypt_cipher)
include_directories(${PROJECT_SOURCE_DIR})

if(LINUX)
  add_compile_options(-DWITH_LINUX)
elseif(APPLE)
  add_compile_options(-DWITH_APPLE) 
else()
  add_compile_options(-DWITH_LINUX)
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(decrypt_cipher decrypt.c hash_table.c)
target_link_libraries(decrypt_cipher ${GTEST_LIBRARIES} -lpthread -lm)
