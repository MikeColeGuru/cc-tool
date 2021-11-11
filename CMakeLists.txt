project(cc-tool)
cmake_minimum_required(VERSION 3.13.0)

find_package(PkgConfig REQUIRED)

find_package(Boost 1.40 COMPONENTS program_options regex filesystem REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

pkg_check_modules(libusb REQUIRED libusb-1.0>=1.0.0)
include_directories(${libusb_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cc-tool "")

add_subdirectory(src)

TARGET_LINK_LIBRARIES( cc-tool LINK_PUBLIC ${Boost_LIBRARIES} ${libusb_LIBRARIES} )
