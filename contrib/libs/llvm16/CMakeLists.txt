
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(utils)

add_library(contrib-libs-llvm16 INTERFACE)
target_include_directories(contrib-libs-llvm16 INTERFACE
  ${YT_BINARY_DIR}/contrib/libs/llvm16/include
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/include
)
target_link_libraries(contrib-libs-llvm16 INTERFACE
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
)
