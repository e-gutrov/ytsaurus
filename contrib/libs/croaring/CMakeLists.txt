
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(contrib-libs-croaring)
target_compile_options(contrib-libs-croaring PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(contrib-libs-croaring PUBLIC
  ${YT_SOURCE_DIR}/contrib/libs/croaring/include
)
target_include_directories(contrib-libs-croaring PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/croaring/include/roaring
)
target_link_libraries(contrib-libs-croaring PUBLIC
  contrib-libs-linux-headers
)
target_sources(contrib-libs-croaring PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/array_util.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/bitset.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/bitset_util.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/array.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/bitset.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/containers.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/convert.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_andnot.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_equal.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_intersection.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_negation.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_subset.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_union.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/mixed_xor.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/containers/run.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/isadetection.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/memory.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/roaring.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/roaring_array.c
  ${YT_SOURCE_DIR}/contrib/libs/croaring/src/roaring_priority_queue.c
)
