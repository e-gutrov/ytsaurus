
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


get_built_tool_path(
  TOOL_protoc_bin
  TOOL_protoc_dependency
  contrib/tools/protoc/bin
  protoc
)
get_built_tool_path(
  TOOL_cpp_styleguide_bin
  TOOL_cpp_styleguide_dependency
  contrib/tools/protoc/plugins/cpp_styleguide
  cpp_styleguide
)
get_built_tool_path(
  TOOL_protoc_bin
  TOOL_protoc_dependency
  contrib/tools/protoc/bin
  protoc
)
get_built_tool_path(
  TOOL_cpp_styleguide_bin
  TOOL_cpp_styleguide_dependency
  contrib/tools/protoc/plugins/cpp_styleguide
  cpp_styleguide
)

add_library(chyt-server-protos)
target_compile_options(chyt-server-protos PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(chyt-server-protos PUBLIC
  ${YT_BINARY_DIR}/yt
)
target_link_libraries(chyt-server-protos PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  yt-yt-ytlib
  yt_proto-yt-core
  contrib-libs-protobuf
)
target_proto_messages(chyt-server-protos PRIVATE
  ${YT_SOURCE_DIR}/yt/chyt/server/protos/clickhouse_service.proto
  ${YT_SOURCE_DIR}/yt/chyt/server/protos/subquery_spec.proto
)
target_proto_addincls(chyt-server-protos
  ./yt
  ${YT_SOURCE_DIR}/yt
  ${YT_BINARY_DIR}
  ${YT_SOURCE_DIR}
  ${YT_SOURCE_DIR}/yt
  ${YT_SOURCE_DIR}/yt
  ${YT_SOURCE_DIR}/contrib/libs/protobuf/src
  ${YT_BINARY_DIR}
  ${YT_SOURCE_DIR}/contrib/libs/protobuf/src
)
target_proto_outs(chyt-server-protos
  --cpp_out=${YT_BINARY_DIR}/yt
  --cpp_styleguide_out=${YT_BINARY_DIR}/yt
)
