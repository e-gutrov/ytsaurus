add_library(Root-Option)
target_compile_options(Root-Option PRIVATE
        $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
        )
target_include_directories(Root-Option PRIVATE
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Option
        )
target_link_libraries(Root-Option PUBLIC
        contrib-libs-linux-headers
        contrib-libs-cxxsupp
        contrib-libs-llvm16
        llvm16-lib-Support
        )

target_sources(Root-Option PRIVATE
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Option/Arg.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Option/ArgList.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Option/Option.cpp
        ${YT_SOURCE_DIR}/contrib/libs/llvm16/lib/Option/OptTable.cpp
        )