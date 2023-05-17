add_library(ExecutionEngine-Jitlink)
target_compile_options(ExecutionEngine-Jitlink PRIVATE
        $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
        )
target_include_directories(ExecutionEngine-Jitlink PRIVATE
    ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink
    )
target_link_libraries(ExecutionEngine-Jitlink PUBLIC
        contrib-libs-linux-headers
        contrib-libs-cxxsupp
        contrib-libs-llvm16
        llvm16-lib-Support
        Root-Option
        )

target_sources(ExecutionEngine-Jitlink PRIVATE
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/aarch64.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFF.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFF_x86_64.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFFDirectiveParser.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFFDirectiveParser.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFFLinkGraphBuilder.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFFLinkGraphBuilder.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/COFFOptions.td
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/DefineExternalSectionStartAndEndSymbols.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/DWARFRecordSectionSplitter.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/EHFrameSupport.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/EHFrameSupportImpl.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELF.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELF_aarch64.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELF_i386.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELF_loongarch.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELF_riscv.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELF_x86_64.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELFLinkGraphBuilder.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/ELFLinkGraphBuilder.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/i386.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/JITLink.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/JITLinkGeneric.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/JITLinkGeneric.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/JITLinkMemoryManager.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/loongarch.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/MachO.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/MachO_arm64.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/MachO_x86_64.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/MachOLinkGraphBuilder.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/MachOLinkGraphBuilder.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/PerGraphGOTAndPLTStubsBuilder.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/riscv.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/SEHFrameSupport.h
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/JITLink/x86_64.cpp
        )