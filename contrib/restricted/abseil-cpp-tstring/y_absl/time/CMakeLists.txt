
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(abseil-cpp-tstring-y_absl-time)
target_compile_options(abseil-cpp-tstring-y_absl-time PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(abseil-cpp-tstring-y_absl-time PUBLIC
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring
)
target_link_libraries(abseil-cpp-tstring-y_absl-time PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  abseil-cpp-tstring-y_absl-base
  abseil-cpp-tstring-y_absl-numeric
  abseil-cpp-tstring-y_absl-strings
)
target_sources(abseil-cpp-tstring-y_absl-time PRIVATE
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/civil_time.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/clock.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/duration.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/format.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/civil_time_detail.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_fixed.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_format.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_if.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_impl.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_info.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_libc.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_lookup.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/time_zone_posix.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src/zone_info_source.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/time/time.cc
)
