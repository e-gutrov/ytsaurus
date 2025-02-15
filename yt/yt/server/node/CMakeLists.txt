
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


add_subdirectory(cellar_node)
add_subdirectory(chaos_node)
add_subdirectory(data_node)
add_subdirectory(tablet_node)
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

add_library(yt-server-node)
target_compile_options(yt-server-node PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(yt-server-node PUBLIC
  ${YT_BINARY_DIR}/yt
)
target_include_directories(yt-server-node PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/sparsehash/src
)
target_link_libraries(yt-server-node PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  library-query-engine
  library-query-row_comparer
  server-node-cellar_node
  server-node-chaos_node
  yt-server-tools
  yt-library-re2
  yt-ytlib-distributed_throttler
  ytserver
  server-lib-io
  server-lib-cellar_agent
  server-lib-chaos_node
  server-lib-chunk_server
  yt-library-containers
  library-containers-disk_manager
  server-lib-exec_node
  server-lib-tablet_server
  server-lib-hydra
  server-lib-hydra2
  server-lib-lsm
  server-lib-rpc
  server-lib-controller_agent
  library-cpp-getopt
  cpp-yt-phdr_cache
  libs-tcmalloc-malloc_extension
  contrib-libs-protobuf
)
target_proto_messages(yt-server-node PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/artifact.proto
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/volume.proto
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/in_memory_service.proto
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/transaction_manager.proto
)
target_sources(yt-server-node PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/server/node/cluster_node/batching_chunk_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/cluster_node/dynamic_config_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/cluster_node/node_resource_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/cluster_node/master_connector.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/cluster_node/bootstrap.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/cluster_node/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/ally_replica_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/artifact.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/blob_chunk.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/blob_reader_cache.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/blob_session.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/bootstrap.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/chunk.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/chunk_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/chunk_meta_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/chunk_registry.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/chunk_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/chunk_reader_sweeper.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/data_node_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/disk_location.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/job.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/job_controller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/journal_chunk.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/journal_dispatcher.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/journal_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/journal_session.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/io_throughput_meter.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/local_chunk_reader.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/location.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/location_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/master_connector.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/medium_directory_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/medium_updater.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/network_statistics.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/offloaded_chunk_read_session.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/p2p.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/session_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/session_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/skynet_http_handler.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/table_schema_cache.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/data_node/ytree_integration.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/bootstrap.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/controller_agent_connector.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/chunk_cache.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/cache_location.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/exec_node_admin_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/gpu_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job_environment.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job_directory_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job_gpu_checker.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job_controller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job_prober_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/job_workspace_builder.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/master_connector.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/private.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/scheduler_connector.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/slot.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/slot_location.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/slot_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/supervisor_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/exec_node/volume_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/job_agent/orchid_service_provider.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/job_agent/job_resource_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/query_agent/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/query_agent/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/query_agent/multiread_request_queue_provider.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/query_agent/query_executor.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/query_agent/query_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/automaton.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/backing_store_cleaner.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/backup_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/bootstrap.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/cached_row.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/chaos_agent.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/distributed_throttler_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/dynamic_store_bits.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hedging_manager_registry.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hint_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_chunk.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_chunk_sweeper.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_lock_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_tablet.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_tablet_scanner.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/hunk_tablet_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/in_memory_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/in_memory_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/lock_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/locking_state.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/lookup.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/lsm_interop.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/master_connector.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/object_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/ordered_chunk_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/ordered_dynamic_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/ordered_store_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/partition.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/partition_balancer.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/relative_replication_throttler.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/replicated_store_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/replication_log.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/row_cache.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/security_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/serialize.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/slot_provider.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/slot_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/sorted_chunk_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/sorted_dynamic_comparer.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/sorted_dynamic_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/sorted_store_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store_compactor.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store_flusher.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store_manager_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store_rotator.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/store_trimmer.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/structured_logger.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/table_config_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/table_replicator.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/table_puller.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_cell_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_cell_snapshot_validator.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_memory_statistics.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_cell_write_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_profiling.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_reader.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_slot.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_snapshot_store.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/tablet_write_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/transaction.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/transaction_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/server/node/tablet_node/versioned_chunk_meta_manager.cpp
)
target_proto_addincls(yt-server-node
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
target_proto_outs(yt-server-node
  --cpp_out=${YT_BINARY_DIR}/yt
  --cpp_styleguide_out=${YT_BINARY_DIR}/yt
)
