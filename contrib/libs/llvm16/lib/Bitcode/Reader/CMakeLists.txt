
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(lib-Bitcode-Reader)
target_compile_options(lib-Bitcode-Reader PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(lib-Bitcode-Reader PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Bitcode/Reader
)
target_link_libraries(lib-Bitcode-Reader PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  contrib-libs-llvm16
  libs-llvm16-include
  lib-Bitstream-Reader
  llvm16-lib-IR
  llvm16-lib-Support
  llvm16-lib-TargetParser
)
target_sources(lib-Bitcode-Reader PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Bitcode/Reader/BitReader.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Bitcode/Reader/BitcodeAnalyzer.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Bitcode/Reader/BitcodeReader.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Bitcode/Reader/MetadataLoader.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Bitcode/Reader/ValueList.cpp
)
