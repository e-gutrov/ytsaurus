
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


get_built_tool_path(
  TOOL_flatc_bin
  TOOL_flatc_dependency
  contrib/tools/flatc/bin
  flatc
)
get_built_tool_path(
  TOOL_flatc_bin
  TOOL_flatc_dependency
  contrib/tools/flatc/bin
  flatc
)
get_built_tool_path(
  TOOL_flatc_bin
  TOOL_flatc_dependency
  contrib/tools/flatc/bin
  flatc
)
get_built_tool_path(
  TOOL_flatc_bin
  TOOL_flatc_dependency
  contrib/tools/flatc/bin
  flatc
)

add_library(yt-client-arrow)
target_compile_options(yt-client-arrow PRIVATE
  -Wdeprecated-this-capture
)
target_link_libraries(yt-client-arrow PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  yt-yt-client
  contrib-libs-flatbuffers
)
target_sources(yt-client-arrow PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/arrow_row_stream_encoder.cpp
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/arrow_row_stream_decoder.cpp
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/public.cpp
  ${YT_BINARY_DIR}/yt/yt/client/arrow/fbs/Message.fbs.cpp
  ${YT_BINARY_DIR}/yt/yt/client/arrow/fbs/Schema.fbs.cpp
  ${YT_BINARY_DIR}/yt/yt/client/arrow/fbs/Tensor.fbs.cpp
  ${YT_BINARY_DIR}/yt/yt/client/arrow/fbs/SparseTensor.fbs.cpp
)
target_fbs_source(yt-client-arrow
  PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/fbs/Message.fbs
  -I
  ${YT_BINARY_DIR}
  -I
  ${YT_SOURCE_DIR}
)
target_fbs_source(yt-client-arrow
  PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/fbs/Schema.fbs
  -I
  ${YT_BINARY_DIR}
  -I
  ${YT_SOURCE_DIR}
)
target_fbs_source(yt-client-arrow
  PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/fbs/Tensor.fbs
  -I
  ${YT_BINARY_DIR}
  -I
  ${YT_SOURCE_DIR}
)
target_fbs_source(yt-client-arrow
  PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/client/arrow/fbs/SparseTensor.fbs
  -I
  ${YT_BINARY_DIR}
  -I
  ${YT_SOURCE_DIR}
)
