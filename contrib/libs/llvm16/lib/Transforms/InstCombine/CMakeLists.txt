
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(lib-Transforms-InstCombine)
target_compile_options(lib-Transforms-InstCombine PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(lib-Transforms-InstCombine PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine
)
target_link_libraries(lib-Transforms-InstCombine PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  contrib-libs-llvm16
  libs-llvm16-include
  llvm16-lib-Analysis
  llvm16-lib-IR
  llvm16-lib-Support
  lib-Transforms-Utils
)
target_sources(lib-Transforms-InstCombine PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineAddSub.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineAndOrXor.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineAtomicRMW.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineCalls.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineCasts.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineCompares.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineLoadStoreAlloca.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineMulDivRem.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineNegator.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombinePHI.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineSelect.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineShifts.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineSimplifyDemanded.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstCombineVectorOps.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Transforms/InstCombine/InstructionCombining.cpp
)
