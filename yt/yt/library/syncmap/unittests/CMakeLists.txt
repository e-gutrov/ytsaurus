
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_executable(yt-yt-library-syncmap-unittests)
target_compile_options(yt-yt-library-syncmap-unittests PRIVATE
  -Wdeprecated-this-capture
)
target_link_libraries(yt-yt-library-syncmap-unittests PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  library-cpp-cpuid_check
  cpp-testing-gtest
  cpp-testing-gtest_main
  yt-yt-core
  yt-library-syncmap
)
target_link_options(yt-yt-library-syncmap-unittests PRIVATE
  -ldl
  -lrt
  -Wl,--no-as-needed
  -fPIC
  -fPIC
  -lpthread
  -lrt
  -ldl
  -lutil
)
target_sources(yt-yt-library-syncmap-unittests PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/library/syncmap/unittests/map_ut.cpp
)
add_test(
  NAME
  yt-yt-library-syncmap-unittests
  COMMAND
  yt-yt-library-syncmap-unittests
)
set_property(
  TEST
  yt-yt-library-syncmap-unittests
  PROPERTY
  LABELS
  SMALL
)
set_property(
  TEST
  yt-yt-library-syncmap-unittests
  PROPERTY
  PROCESSORS
  1
)
target_allocator(yt-yt-library-syncmap-unittests
  cpp-malloc-tcmalloc
  libs-tcmalloc-no_percpu_cache
)
vcs_info(yt-yt-library-syncmap-unittests)
