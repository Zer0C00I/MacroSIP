cmake_minimum_required(VERSION 3.19)
project(MacroSIP VERSION 3.22.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------- strict security / hardening flags ----------
add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -Wformat=2 -Wformat-security -Wformat-overflow=2
    -Wconversion -Wsign-conversion
    -Wcast-align -Wcast-qual
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wnull-dereference
    -Wunused
    -Wshadow
    -Wpointer-arith
    -Wwrite-strings
    -Wswitch-enum
    -Wmissing-include-dirs
    -Wredundant-decls
    -Wundef

    # Security hardening
    -fstack-protector-strong
    -fstack-clash-protection
    -fcf-protection
    -fPIE
    -D_FORTIFY_SOURCE=2
    -D_GLIBCXX_ASSERTIONS
)

add_link_options(
    -pie
    -Wl,-z,relro
    -Wl,-z,now
    -Wl,-z,noexecstack
)

# ---------- Qt ----------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Multimedia)
set(QT_LIBS Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Multimedia)
message(STATUS "Using Qt ${Qt6_VERSION}")

# ---------- Optional PJSIP ----------
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(PJSIP IMPORTED_TARGET libpjproject)
endif()

option(ENABLE_PJSIP "Enable PJSIP SIP stack integration" ON)
if(ENABLE_PJSIP AND PJSIP_FOUND)
    message(STATUS "PJSIP found – SIP support enabled")
    add_compile_definitions(PJSIP_ENABLED)
else()
    message(STATUS "PJSIP not found – building without SIP (stub mode)")
    set(ENABLE_PJSIP OFF)
endif()

# ---------- OpenSSL (optional, for crypto) ----------
find_package(OpenSSL QUIET)
if(OpenSSL_FOUND)
    message(STATUS "OpenSSL found – encryption enabled")
    add_compile_definitions(OPENSSL_ENABLED)
endif()

# ---------- sources ----------
add_subdirectory(src)

# ---------- tests ----------
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
