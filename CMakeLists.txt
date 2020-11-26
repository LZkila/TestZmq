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

find_package(ZeroMQ CONFIG REQUIRED)
if(ZeroMQ_NOTFOUND)
    message(WARNING "...zeromq not found")
endif()

find_package(glog CONFIG REQUIRED)
if(glog_NOTFOUND)
    message(WARNING "...glog not found")
endif()

find_package(GTest CONFIG REQUIRED)
if(GTest_NOTFOUND)
    message(WARNING "...gtest not found")
endif()


file(GLOB FILE_TESTCPP ${DIR_SRC}/*.cpp)
add_executable(${APP_TESTCPP}
    ${FILE_TESTCPP}
    )

# target_include_directories(${APP_TESTCPP}
#     PRIVATE
#     ${GTEST_INCLUDE_DIR}
#     )

target_link_libraries(${APP_TESTCPP}
    PRIVATE
    glog::glog
    GTest::gtest
    GTest::gmock
    libzmq
    ${ZeroMQ_LIBRARY}
    )

enable_testing()
add_test(NAME ${APP_TESTCPP} COMMAND ${APP_TESTCPP})