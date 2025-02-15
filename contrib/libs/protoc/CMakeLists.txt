
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(contrib-libs-protoc)
target_compile_options(contrib-libs-protoc PRIVATE
  -DHAVE_CONFIG_H
  -DHAVE_PTHREAD=1
  -DHAVE_ZLIB=1
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(contrib-libs-protoc PUBLIC
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src
)
target_link_libraries(contrib-libs-protoc PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  contrib-libs-protobuf
)
target_sources(contrib-libs-protoc PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/code_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/command_line_interface.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_enum.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_enum_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_extension.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_file.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_helpers.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_map_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_message.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_message_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_padding_optimizer.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_parse_function_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_primitive_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_service.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/cpp/cpp_string_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_doc_comment.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_enum.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_enum_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_field_base.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_helpers.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_map_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_message.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_message_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_primitive_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_reflection_class.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_repeated_enum_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_repeated_message_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_repeated_primitive_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_source_generator_base.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/csharp/csharp_wrapper_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/importer.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_context.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_doc_comment.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_enum.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_enum_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_enum_field_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_enum_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_extension.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_extension_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_file.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_generator_factory.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_helpers.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_kotlin_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_map_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_map_field_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_message.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_message_builder.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_message_builder_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_message_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_message_field_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_message_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_name_resolver.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_primitive_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_primitive_field_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_service.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_shared_code_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_string_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/java/java_string_field_lite.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/js/js_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/js/well_known_types_embed.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_enum.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_enum_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_extension.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_file.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_helpers.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_map_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_message.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_message_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_oneof.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/objectivec/objectivec_primitive_field.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/parser.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/perlxs/perlxs_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/perlxs/perlxs_helpers.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/php/php_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/plugin.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/plugin.pb.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/python/python_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/ruby/ruby_generator.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/subprocess.cc
  ${YT_SOURCE_DIR}/contrib/libs/protoc/src/google/protobuf/compiler/zip_writer.cc
)
