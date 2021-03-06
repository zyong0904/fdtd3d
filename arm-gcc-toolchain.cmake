set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_SYSTEM_PROCESSOR armv7l)

set(TOOLCHAIN "arm-linux-gnueabihf")
set(TOOLCHAIN_VERSION "8")
set(CROSS_ROOTFS "/mnt/rpi")

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

include_directories(BEFORE SYSTEM ${CROSS_ROOTFS}/usr/include/c++/${TOOLCHAIN_VERSION})
include_directories(BEFORE SYSTEM ${CROSS_ROOTFS}/usr/include/${TOOLCHAIN}/c++/${TOOLCHAIN_VERSION})

set(CMAKE_SYSROOT "${CROSS_ROOTFS}")

add_link_options("-L${CROSS_ROOTFS}/lib")
add_link_options("-L${CROSS_ROOTFS}/usr/lib")
add_link_options("-L${CROSS_ROOTFS}/usr/lib/gcc/${TOOLCHAIN}/${TOOLCHAIN_VERSION}")
add_link_options("-L${CROSS_ROOTFS}/usr/lib/${TOOLCHAIN}/")
add_link_options("-L${CROSS_ROOTFS}/lib/${TOOLCHAIN}/")

add_compile_options(-march=armv8-a+crc+simd)
add_compile_options(-mtune=cortex-a72)
add_compile_options(-mfpu=crypto-neon-fp-armv8)
add_compile_options(-mfloat-abi=hard)
add_compile_options(-mthumb)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
