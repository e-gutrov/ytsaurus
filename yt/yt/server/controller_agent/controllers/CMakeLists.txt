
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(server-controller_agent-controllers)
target_compile_options(server-controller_agent-controllers PRIVATE
  -Wdeprecated-this-capture
)
target_link_libraries(server-controller_agent-controllers PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  ytserver
  server-lib-chunk_pools
  server-lib-tablet_server
  yt-library-safe_assert
)
target_sources(server-controller_agent-controllers PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/aggregated_job_statistics.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/alert_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/auto_merge_director.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/auto_merge_task.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/chunk_pool_adapters.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/competitive_job_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/data_balancer.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/data_flow_graph.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/extended_job_resources.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/job_info.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/job_helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/job_memory.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/job_splitter.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/layer_probing_job_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/operation_controller_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/ordered_controller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/probing_job_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/speculative_job_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/sort_controller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/sorted_controller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/table.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/task.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/unordered_controller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/controller_agent/controllers/vanilla_controller.cpp
)
