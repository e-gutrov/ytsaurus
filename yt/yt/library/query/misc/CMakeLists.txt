
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(library-query-misc)
target_compile_options(library-query-misc PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(library-query-misc PUBLIC
  ${YT_BINARY_DIR}/yt
)
target_link_libraries(library-query-misc PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  cpp-yt-assert
)
target_sources(library-query-misc PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/library/query/misc/objects_holder.cpp
  ${YT_SOURCE_DIR}/yt/yt/library/query/misc/function_context.cpp
)
