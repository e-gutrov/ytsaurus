
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


find_package(ZLIB REQUIRED)
find_package(c-ares REQUIRED)
add_subdirectory(actions)
add_subdirectory(bus)
add_subdirectory(compression)
add_subdirectory(concurrency)
add_subdirectory(crypto)
add_subdirectory(http)
add_subdirectory(https)
add_subdirectory(json)
add_subdirectory(logging)
add_subdirectory(misc)
add_subdirectory(net)
add_subdirectory(profiling)
add_subdirectory(rpc)
add_subdirectory(service_discovery)
add_subdirectory(test_framework)
add_subdirectory(ypath)
add_subdirectory(yson)
add_subdirectory(ytree)

add_library(yt-yt-core)
target_compile_options(yt-yt-core PRIVATE
  -mpclmul
  -Wdeprecated-this-capture
)
target_link_libraries(yt-yt-core PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  contrib-libs-snappy
  ZLIB::ZLIB
  contrib-libs-zstd
  contrib-libs-lzmasdk
  contrib-libs-libbz2
  c-ares::c-ares
  contrib-libs-farmhash
  contrib-libs-yajl
  contrib-libs-lz4
  cpp-threading-thread_local
  cpp-streams-brotli
  cpp-yt-assert
  cpp-yt-containers
  cpp-yt-logging
  cpp-yt-misc
  cpp-yt-memory
  cpp-yt-string
  cpp-yt-yson
  cpp-yt-yson_string
  cpp-ytalloc-api
  yt-yt-build
  isa-l_crc_yt_patch
  yt_proto-yt-core
  cpp-yt-backtrace
  cpp-yt-coding
  cpp-yt-malloc
  cpp-yt-small_containers
  cpp-yt-system
  cpp-yt-threading
  yt-library-syncmap
  yt-library-undumpable
  library-ytprof-api
  yt-library-profiling
  library-profiling-resource_tracker
  yt-library-tracing
  backtrace-cursors-libunwind
)
target_sources(yt-yt-core PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/core/actions/cancelable_context.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/actions/current_invoker.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/actions/future.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/actions/invoker_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/actions/invoker_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/actions/invoker_util.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/connection.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/dispatcher.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/dispatcher_impl.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/packet.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/client.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/bus/tcp/server.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/brotli.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/bzip2.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/codec.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/stream.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/lz.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/lzma.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/snappy.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/zlib.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/compression/zstd.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/action_queue.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/async_semaphore.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/async_rw_lock.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/async_stream.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/async_stream_pipe.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/coroutine.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/delayed_executor.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/execution_stack.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fair_share_action_queue.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fair_share_invoker_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fair_share_invoker_queue.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fair_share_thread_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fair_share_queue_scheduler_thread.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fair_throttler.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fiber.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fiber_scheduler_thread.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/finalizer_thread.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/fls.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/new_fair_share_thread_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/notify_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/invoker_alarm.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/invoker_queue.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/notification_handle.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/periodic_executor.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/periodic_yielder.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/pollable_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/profiling_helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/propagating_storage.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/quantized_executor.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/scheduler_thread.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/single_queue_scheduler_thread.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/thread.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/suspendable_action_queue.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/thread_affinity.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/thread_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/thread_pool_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/thread_pool_poller.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/throughput_throttler.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/two_level_fair_share_thread_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/lease_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/concurrency/count_down_latch.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/compression.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/formatter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/fluent_log.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/log_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/logger_owner.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/pattern.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/serializable_logger.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/stream_output.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/log_writer_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/file_log_writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/stream_log_writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/random_access_gzip.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/logging/zstd_compression.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/arithmetic_formula.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/backoff_strategy.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/backoff_strategy_config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/bitmap.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/bit_packed_unsigned_vector.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/bit_packing.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/blob_output.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/bloom_filter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/checksum.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/coro_pipe.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/crash_handler.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/digest.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/dnf.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/error.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/error_code.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/ema_counter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/fs.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/hazard_ptr.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/hedging_manager.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/histogram.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/historic_usage_aggregator.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/hr_timer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/id_generator.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/linear_probe.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/memory_reference_tracker.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/memory_usage_tracker.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/relaxed_mpsc_queue.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/parser_helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/pattern_formatter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/phoenix.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/pool_allocator.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/proc.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/protobuf_helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/random.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/ref_counted_tracker.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/ref_counted_tracker_statistics_producer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/ref_counted_tracker_profiler.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/serialize.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/shutdown.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/signal_registry.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/slab_allocator.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/statistics.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/cache_config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/utf8_decoder.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/zerocopy_output_writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/address.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/connection.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/dialer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/dns_resolver.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/listener.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/local_address.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/net/socket.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/profiling/timing.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/authentication_identity.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/authenticator.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/balancing_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/caching_channel_factory.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/channel_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/client.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/dispatcher.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/dynamic_channel_pool.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/hedging_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/local_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/local_server.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/message.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/message_format.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/null_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/per_user_request_queue_provider.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/protocol_version.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/request_queue_provider.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/response_keeper.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/retrying_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/roaming_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/serialized_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/server_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/service.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/service_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/static_channel_factory.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/stream.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/throttling_channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/viable_peer_registry.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/bus/server.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/rpc/bus/channel.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/service_discovery/service_discovery.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/threading/spin_wait_slow_path_logger.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/tracing/allocation_tags.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/tracing/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/tracing/public.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/utilex/random.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ypath/stack.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ypath/token.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ypath/tokenizer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ypath/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/async_consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/async_writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/attribute_consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/forwarding_consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/lexer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/null_consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/parser.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/producer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/protobuf_interop.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/protobuf_interop_options.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/protobuf_interop_unknown_fields.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/pull_parser.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/pull_parser_deserialize.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/stream.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/string.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/string_filter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/syntax_checker.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/token.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/token_writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/tokenizer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/string_merger.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/yson/ypath_designated_consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/attribute_consumer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/attributes.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/attribute_filter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/convert.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/ephemeral_attribute_owner.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/ephemeral_node_factory.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/exception_helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/interned_attributes.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/node.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/node_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/permission.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/request_complexity_limiter.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/serialize.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/static_service_dispatcher.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/system_attribute_provider.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/tree_builder.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/tree_visitor.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/virtual.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/service_combiner.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/ypath_client.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/ypath_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/ypath_resolver.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/ypath_service.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/yson_serializable.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/yson_struct.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytree/yson_struct_detail.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/json/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/json/json_callbacks.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/json/helpers.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/json/json_parser.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/json/json_writer.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytalloc/bindings.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytalloc/config.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/ytalloc/statistics_producer.cpp
)

add_global_library_for(yt-yt-core.global yt-yt-core)
target_compile_options(yt-yt-core.global PRIVATE
  -mpclmul
  -Wdeprecated-this-capture
)
target_link_libraries(yt-yt-core.global PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  contrib-libs-snappy
  ZLIB::ZLIB
  contrib-libs-zstd
  contrib-libs-lzmasdk
  contrib-libs-libbz2
  c-ares::c-ares
  contrib-libs-farmhash
  contrib-libs-yajl
  contrib-libs-lz4
  cpp-threading-thread_local
  cpp-streams-brotli
  cpp-yt-assert
  cpp-yt-containers
  cpp-yt-logging
  cpp-yt-misc
  cpp-yt-memory
  cpp-yt-string
  cpp-yt-yson
  cpp-yt-yson_string
  cpp-ytalloc-api
  yt-yt-build
  isa-l_crc_yt_patch
  yt_proto-yt-core
  cpp-yt-backtrace
  cpp-yt-coding
  cpp-yt-malloc
  cpp-yt-small_containers
  cpp-yt-system
  cpp-yt-threading
  yt-library-syncmap
  yt-library-undumpable
  library-ytprof-api
  yt-library-profiling
  library-profiling-resource_tracker
  yt-library-tracing
  backtrace-cursors-libunwind
)
target_sources(yt-yt-core.global PRIVATE
  ${YT_SOURCE_DIR}/yt/yt/core/logging/log.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/assert.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/guid.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/misc/ref_tracked.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/tracing/allocation_hooks.cpp
  ${YT_SOURCE_DIR}/yt/yt/core/tracing/trace_context.cpp
)
