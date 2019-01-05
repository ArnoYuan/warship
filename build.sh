#!/bin/sh

project_dir=`pwd`

package_dir=$project_dir"/../packages"

toolchain_dir="/home/seeing-zynq/Development/develop/toolchain"

toolchain_prefix=$toolchain_dir"/gcc-arm-none-eabi-7-2018-q2-update"

cmake_toolchain_file=$toolchain_dir"/stm32-cmake/cmake/gcc_stm32.cmake"


mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug -DTOOLCHAIN_PREFIX=$toolchain_prefix -DTARGET_TRIPLET=arm-none-eabi -DCMAKE_TOOLCHAIN_FILE=$cmake_toolchain_file $project_dir -DPACKAGES_DIR=$package_dir

make
