cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(kamishibai)

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)
option(USE_LIBCXX "Use libc++ for the C++ standard library" ON)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if(USE_LIBCXX)
      message("-- Locating libc++...")
      find_library(LIBCXX_LIBRARY NAMES c++ cxx)
      if(LIBCXX_LIBRARY)
        message("-- Located libc++, using it.")
        set(LIBCXX_OPTIONS "-stdlib=libc++")
        message("--     Locating libc++'s abi...")
        find_library(LIBCXXABI_LIBRARY NAMES c++abi)
        find_library(LIBCXXRT_LIBRARY NAMES cxxrt)
        if(LIBCXXABI_LIBRARY)
          message("--     Found libc++abi, using it.")
          set(CXXABI_LIBRARY ${LIBCXXABI_LIBRARY})
        elseif(LIBCXXRT_LIBRARY)
          message("--     Found libcxxrt, using it.")
          set(CXXABI_LIBRARY ${LIBCXXRT_LIBRARY})
        else()
          message("--     No abi library found. "
            "Attempting to continue without one...")
        endif()
      else()
        message("-- Could not find libc++, will not use it.")
      endif()
    endif()
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBCXX_OPTIONS}")
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${CXXABI_LIBRARY}")

  # if we don't already set the standard for the compiler, detect the
  # best one available and use it
  if(NOT "${CMAKE_CXX_FLAGS}" MATCHES "std=c\\+\\+(0x|11|1y|14)")
    check_cxx_compiler_flag(-std=c++14 HAS_CXX14)
    if(HAS_CXX14)
      message("-- Compiler supports C++14 (using it)")
      set(STDOPT "-std=c++14")
    endif()

    if(NOT STDOPT)
      check_cxx_compiler_flag(-std=c++1y HAS_CXX1Y)
      if(HAS_CXX1Y)
        message("-- Compiler supports C++1y (using it)")
        set(STDOPT "-std=c++1y")
      endif()
    endif()

    if(NOT STDOPT)
      check_cxx_compiler_flag(-std=c++11 HAS_CXX11)
      if(HAS_CXX11)
        message("-- Compiler supports C++11 (using it)")
        set(STDOPT "-std=c++11")
      endif()
    endif()

    if(NOT STDOPT)
      check_cxx_compiler_flag(-std=c++0x HAS_CXX0X)
      if(HAS_CXXOX)
        message("-- Compiler supports C++0x (using it)")
        set(STDOPT "-std=c++0x")
      endif()
    endif()

    if(NOT STDOPT)
      message(FATAL_ERROR
        "cpptoml requires a compiler with at least C++0x support")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STDOPT}")
  endif()
endif()


project(kamishibai-server)

set(KAMISHIBAI_MAJOR_VERSION 0)
set(KAMISHIBAI_MINOR_VERSION 2)
set(KAMISHIBAI_PATCH_VERSION 1)
set(KAMISHIBAI_VERSION ${KAMISHIBAI_MAJOR_VERSION}.${KAMISHIBAI_MINOR_VERSION}.${KAMISHIBAI_PATCH_VERSION})
set(KAMISHIBAI_BUILD_TYPE ${CMAKE_BUILD_TYPE})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
endif()

find_package(Threads REQUIRED)
find_package(ImageMagick COMPONENTS Magick++)

include_directories(
  ${kamishibai_SOURCE_DIR}/src
  ${kamishibai-server_SOURCE_DIR}/src
  ${kamishibai_SOURCE_DIR}/dist/{cpptoml,plog,cmdline}/include
  ${ImageMagick_INCLUDE_DIRS}
  /usr/local/include
  /usr/include)
link_directories(/usr/local/lib /usr/lib)

file(GLOB_RECURSE KAMISHIBAI_SERVER_SRCS ./src/*.cc)

add_executable(cv_test01 cv_test01.cc)
target_link_libraries(cv_test01  opencv_core opencv_imgproc opencv_highgui Threads::Threads ${ImageMagick_LIBRARIES})

set_target_properties(cv_test01
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
)

add_executable(cv_test02 cv_test02.cc)
target_link_libraries(cv_test02  opencv_core opencv_imgproc opencv_highgui Threads::Threads ${ImageMagick_LIBRARIES})

set_target_properties(cv_test02
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
)

add_executable(cv_test03 cv_test03.cc)
target_link_libraries(cv_test03 opencv_core opencv_imgproc opencv_highgui Threads::Threads ${ImageMagick_LIBRARIES})

set_target_properties(cv_test03
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
)
