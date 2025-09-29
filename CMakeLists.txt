cmake_minimum_required(VERSION 3.21)
message("Using toolchain file ${CMAKE_TOOLCHAIN_FILE}.")

########################################################################################################################
## Define project
########################################################################################################################
project(
        SlaveTatsNG
        VERSION 0.8.1
        DESCRIPTION "SlaveTats as SKSE plugin."
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.rc
        @ONLY)

set(sources
        ${CMAKE_CURRENT_BINARY_DIR}/version.rc)



set(headers ${headers}
	include/JContainers/jc_interface.h
	include/JContainers/jcontainers_constants.h
	include/SlaveTatsNG_Interface.h
	include/VMTHook.h
	include/cache.h
	include/config.h
	include/constants.h
	include/high_level_api.h
	include/jcontainers_wrapper.h
	include/logging.h
	include/ni_node_override_lock.h
	include/nioverride_impl.h
	include/nioverride_impl_current.h
	include/nioverride_wrapper.h
	include/overlays.h
	include/papyrus_cache.h
	include/papyrus_constants.h
	include/papyrus_high_level_api.h
	include/papyrus_interface.h
	include/papyrus_logging.h
	include/papyrus_overlays.h
	include/papyrus_primary_api.h
	include/papyrus_query.h
	include/papyrus_tattoo.h
	include/papyrus_tattoo_magic.h
	include/primary_api.h
	include/query.h
	include/skee-modders-resource-v0-4-19-16/SKEE_IPluginInterface.h
	include/skse64_native_papyrus.h
	include/tattoo.h
	include/tattoo_magic.h
	include/threading.h
	include/vm_hook.h
	include/utility.h
	include/skee_addresses.h
	include/nioverride_impl_legacy.h
	src/PCH.h
)

set(sources ${sources}
	src/SlaveTatsNG_Interface.cpp
	src/VMTHook.cpp
	src/cache.cpp
	src/config.cpp
	src/constants.cpp
	src/high_level_api.cpp
	src/jcontainers_wrapper.cpp
	src/logging.cpp
	src/main.cpp
	src/ni_node_override_lock.cpp
	src/nioverride_wrapper.cpp
	src/overlays.cpp
	src/papyrus_cache.cpp
	src/papyrus_constants.cpp
	src/papyrus_high_level_api.cpp
	src/papyrus_interface.cpp
	src/papyrus_logging.cpp
	src/papyrus_overlays.cpp
	src/papyrus_primary_api.cpp
	src/papyrus_query.cpp
	src/papyrus_tattoo.cpp
	src/papyrus_tattoo_magic.cpp
	src/primary_api.cpp
	src/query.cpp
	src/skse64_native_papyrus.cpp
	src/tattoo.cpp
	src/tattoo_magic.cpp
	src/threading.cpp
	src/utility.cpp
	src/skee_addresses.cpp
	src/vm_hook.cpp
	src/nioverride_impl_legacy.cpp
)

########################################################################################################################
## Configure target DLL
########################################################################################################################
find_package(CommonLibSSE CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(xbyak CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-hash-library)
find_path(CLIB_UTIL_INCLUDE_DIRS "ClibUtil/utils.hpp")

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${headers} ${sources})
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_include_directories(${PROJECT_NAME}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/cmake>
        $<INSTALL_INTERFACE:src>)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		${CLIB_UTIL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
		magic_enum::magic_enum
		xbyak::xbyak
		nlohmann_json::nlohmann_json
		unofficial::hash-library
        )

target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        src/PCH.h)
