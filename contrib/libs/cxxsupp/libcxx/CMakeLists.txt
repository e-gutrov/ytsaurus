
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(libs-cxxsupp-libcxx)
target_compile_options(libs-cxxsupp-libcxx PUBLIC
  -nostdinc++
  -DLIBCXX_BUILDING_LIBCXXRT
  -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES
)
target_compile_options(libs-cxxsupp-libcxx PRIVATE
  -D_LIBCPP_BUILDING_LIBRARY
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(libs-cxxsupp-libcxx PUBLIC
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/include
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxxrt/include
)
target_include_directories(libs-cxxsupp-libcxx PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src
)
target_link_libraries(libs-cxxsupp-libcxx PUBLIC
  contrib-libs-linux-headers
  libs-cxxsupp-libcxxabi-parts
  libs-cxxsupp-libcxxrt
  libs-cxxsupp-builtins
)
target_sources(libs-cxxsupp-libcxx PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/algorithm.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/any.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/assert.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/atomic.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/barrier.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/bind.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/charconv.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/chrono.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/condition_variable.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/condition_variable_destructor.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/debug.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/exception.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/filesystem/directory_iterator.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/filesystem/operations.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/functional.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/future.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/hash.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/ios.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/ios.instantiations.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/iostream.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/legacy_pointer_safety.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/locale.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/memory.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/mutex.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/mutex_destructor.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/optional.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/random.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/random_shuffle.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/regex.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/ryu/d2fixed.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/ryu/d2s.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/ryu/f2s.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/shared_mutex.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/stdexcept.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/string.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/strstream.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/system_error.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/thread.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/typeinfo.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/utility.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/valarray.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/variant.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/vector.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/format.cpp
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/libcxx/src/new.cpp
)
