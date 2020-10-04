cmake_minimum_required(VERSION 3.16.3)
project (decrypt_cipher)
include_directories(${PROJECT_SOURCE_DIR})

if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(LINUX)
  add_compile_options(-DWITH_LINUX)
elseif(APPLE)
  add_compile_options(-DWITH_APPLE) 
else()
  add_compile_options(-DWITH_LINUX)
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(decrypt_cipher decrypt_cipher_app.c decrypt.c hash_table.c)
target_link_libraries(decrypt_cipher ${GTEST_LIBRARIES} -lpthread -lm)

add_executable(run_all_tests run_all_tests.cc hash_table_tests.cc hash_table.c decrypt_cipher_tests.cc decrypt.c)
target_link_libraries(run_all_tests ${GTEST_LIBRARIES} -lpthread -lm)
