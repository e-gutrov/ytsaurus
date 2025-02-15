
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


find_package(OpenSSL REQUIRED)

add_library(libs-poco-NetSSL_OpenSSL)
target_compile_options(libs-poco-NetSSL_OpenSSL PRIVATE
  -DPOCO_ENABLE_CPP11
  -DPOCO_ENABLE_CPP14
  -DPOCO_NO_AUTOMATIC_LIBS
  -DPOCO_UNBUNDLED
  -DPOCO_OS_FAMILY_UNIX
  -DPOCO_HAVE_FD_EPOLL
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)
target_include_directories(libs-poco-NetSSL_OpenSSL PUBLIC
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/include
)
target_include_directories(libs-poco-NetSSL_OpenSSL PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/poco/Crypto/include
  ${YT_SOURCE_DIR}/contrib/libs/poco/Foundation/include
  ${YT_SOURCE_DIR}/contrib/libs/poco/Net/include
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src
  ${YT_SOURCE_DIR}/contrib/libs/poco/Util/include
)
target_link_libraries(libs-poco-NetSSL_OpenSSL PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  OpenSSL::OpenSSL
  libs-poco-Crypto
  libs-poco-Foundation
  libs-poco-JSON
  libs-poco-Net
  libs-poco-Util
  libs-poco-XML
)
target_sources(libs-poco-NetSSL_OpenSSL PRIVATE
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/AcceptCertificateHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/CertificateHandlerFactory.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/CertificateHandlerFactoryMgr.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/ConsoleCertificateHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/Context.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/HTTPSClientSession.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/HTTPSSessionInstantiator.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/HTTPSStreamFactory.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/InvalidCertificateHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/KeyConsoleHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/KeyFileHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/PrivateKeyFactory.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/PrivateKeyFactoryMgr.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/PrivateKeyPassphraseHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/RejectCertificateHandler.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SSLException.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SSLManager.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SecureSMTPClientSession.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SecureServerSocket.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SecureServerSocketImpl.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SecureSocketImpl.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SecureStreamSocket.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/SecureStreamSocketImpl.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/Session.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/Utility.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/VerificationErrorArgs.cpp
  ${YT_SOURCE_DIR}/contrib/libs/poco/NetSSL_OpenSSL/src/X509Certificate.cpp
)
