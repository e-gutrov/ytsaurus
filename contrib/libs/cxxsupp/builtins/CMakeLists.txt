
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(libs-cxxsupp-builtins)
target_compile_options(libs-cxxsupp-builtins PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_link_libraries(libs-cxxsupp-builtins PUBLIC
  contrib-libs-linux-headers
)
target_sources(libs-cxxsupp-builtins PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/addtf3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/ashlti3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/clzti2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/comparetf2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/divdc3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/divsc3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/divtf3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/divti3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/divxc3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/extenddftf2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/extendsftf2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixdfti.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixsfti.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixtfdi.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixtfsi.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixunsdfti.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixunssfti.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixunstfdi.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixunstfsi.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixunstfti.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/fixunsxfti.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floatditf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floatsitf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floattidf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floattisf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floattixf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floatunditf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floatunsitf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floatuntidf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/floatuntisf.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/gcc_personality_v0.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/int_util.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/lshrti3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/modti3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/muldc3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/muloti4.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/mulsc3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/multf3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/mulxc3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/popcountdi2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/subtf3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/trunctfdf2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/trunctfsf2.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/udivmodti4.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/udivti3.c
  ${YT_SOURCE_DIR}/contrib/libs/cxxsupp/builtins/umodti3.c
)
