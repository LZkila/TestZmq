cmake_minimum_required(VERSION 3.19)

set(DIR_VCPKG_ROOT "/Users/lzkila/soft/git/vcpkg")
set(CMAKE_TOOLCHAIN_FILE ${DIR_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
set(VCPKG_TARGET_TRIPLET "x64-osx-dynamic" CACHE STRING "")

project(TestCpp LANGUAGES CXX)

set(DIR_3RDPARTY ${DIR_VCPKG_ROOT}/installed/x64-osx-dynamic)
# list(APPEND CMAKE_PREFIX_PATH ${DIR_3RDPARTY})

set(DIR_SRC ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_TESTCPP testcpp)

include_directories(
    ${DIR_3RDPARTY}/include
)

# find_package(ZeroMQ CONFIG REQUIRED)
# if(ZeroMQ_NOTFOUND)
#     message(WARNING "...zeromq not found")
# endif()

find_package(cppzmq CONFIG REQUIRED)
if(cppzmq_NOTFOUND)
    message(WARNING "...cppzmq not found")
endif()

find_package(glog CONFIG REQUIRED)
if(glog_NOTFOUND)
    message(WARNING "...glog not found")
endif()

find_package(GTest CONFIG REQUIRED)
if(GTest_NOTFOUND)
    message(WARNING "...gtest not found")
endif()

find_package(msgpack CONFIG REQUIRED)
if(msgpack_NOTFOUND)
    message(WARNING "...msgpack not found")
endif()

find_package(fmt CONFIG REQUIRED)
if(fmt_NOTFOUND)
    message(WARNING "...fmt not found")
endif()

file(GLOB FILE_TESTCPP ${DIR_SRC}/tests/*.cpp)
file(GLOB FILE_ZMQ ${DIR_SRC}/zmq/*.cpp)
source_group(tests FILES ${FILE_TESTCPP})
source_group(zmq FILES ${FILE_ZMQ})
add_executable(${APP_TESTCPP}
    ${DIR_SRC}/main.cpp
    ${FILE_TESTCPP}
    ${FILE_ZMQ}
    )

target_include_directories(${APP_TESTCPP}
    PRIVATE
    ${DIR_SRC}
    )

target_link_libraries(${APP_TESTCPP}
    PRIVATE
    glog::glog
    GTest::gtest
    GTest::gmock
    cppzmq
    msgpackc-cxx
    fmt::fmt
    )

enable_testing()
add_test(NAME ${APP_TESTCPP} COMMAND ${APP_TESTCPP})