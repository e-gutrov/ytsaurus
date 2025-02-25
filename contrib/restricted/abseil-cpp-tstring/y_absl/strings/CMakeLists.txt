
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(abseil-cpp-tstring-y_absl-strings)
target_compile_options(abseil-cpp-tstring-y_absl-strings PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(abseil-cpp-tstring-y_absl-strings PUBLIC
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring
)
target_link_libraries(abseil-cpp-tstring-y_absl-strings PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  abseil-cpp-tstring-y_absl-base
  abseil-cpp-tstring-y_absl-numeric
)
target_sources(abseil-cpp-tstring-y_absl-strings PRIVATE
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/crc32c.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/cpu_detect.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/crc.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/crc_cord_state.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/crc_memcpy_fallback.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/crc_memcpy_x86_64.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/crc_non_temporal_memcpy.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/crc/internal/crc_x86_arm_combined.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/status/statusor.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/ascii.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/charconv.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/cord.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/cord_analysis.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/cord_buffer.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/escaping.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/charconv_bigint.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/charconv_parse.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_internal.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_rep_btree.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_rep_btree_navigator.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_rep_btree_reader.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_rep_consume.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_rep_crc.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cord_rep_ring.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cordz_functions.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cordz_handle.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cordz_info.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/cordz_sample_token.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/damerau_levenshtein_distance.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/escaping.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/memutil.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/ostringstream.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/str_format/arg.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/str_format/bind.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/str_format/extension.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/str_format/float_conversion.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/str_format/output.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/str_format/parser.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/stringify_sink.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/internal/utf8.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/match.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/numbers.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/str_cat.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/str_replace.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/str_split.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/string_view.cc
  ${YT_SOURCE_DIR}/contrib/restricted/abseil-cpp-tstring/y_absl/strings/substitute.cc
)
