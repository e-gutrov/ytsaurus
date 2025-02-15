
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(llvm16-lib-Object)
target_compile_options(llvm16-lib-Object PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(llvm16-lib-Object PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object
)
target_link_libraries(llvm16-lib-Object PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  contrib-libs-llvm16
  libs-llvm16-include
  llvm16-lib-BinaryFormat
  lib-Bitcode-Reader
  llvm16-lib-IR
  llvm16-lib-IRReader
  llvm16-lib-MC
  lib-MC-MCParser
  llvm16-lib-Support
  llvm16-lib-TargetParser
  llvm16-lib-TextAPI
)
target_sources(llvm16-lib-Object PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/Archive.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/ArchiveWriter.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/Binary.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/BuildID.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/COFFImportFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/COFFModuleDefinition.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/COFFObjectFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/DXContainer.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/Decompressor.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/ELF.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/ELFObjectFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/Error.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/FaultMapParser.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/IRObjectFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/IRSymtab.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/MachOObjectFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/MachOUniversal.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/MachOUniversalWriter.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/Minidump.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/ModuleSymbolTable.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/Object.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/ObjectFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/OffloadBinary.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/RecordStreamer.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/RelocationResolver.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/SymbolSize.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/SymbolicFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/TapiFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/TapiUniversal.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/WasmObjectFile.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/WindowsMachineFlag.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/WindowsResource.cpp
  ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Object/XCOFFObjectFile.cpp
)
