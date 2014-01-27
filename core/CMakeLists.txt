# Add source files for the library

INCLUDE_DIRECTORIES(rpc usb hal utils)

FILE(GLOB LIB_SOURCE_FILES 
  "rpc/*.cpp"
  "api/*.cc"
  "hal/*.cc"
  "utils/*.cc"
  )

FILE(GLOB LIB_HEADER_FILES
  "rpc/*.h"
  "usb/*.h"
  "api/*.h"
  "hal/*.h"
  "utils/*.h"
  )

IF(USE_FTD2XX)
  FILE(GLOB SOURCE_FILES_FTDI "usb/USBInterface.libftd2xx.cc")
ELSE(USE_FTD2XX)
  FILE(GLOB SOURCE_FILES_FTDI "usb/USBInterface.libftdi.cc")
ENDIF(USE_FTD2XX)
SET(LIB_SOURCES ${LIB_SOURCE_FILES} ${SOURCE_FILES_FTDI})

ADD_LIBRARY( ${PROJECT_NAME} SHARED ${LIB_SOURCES} )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${FTDI_LINK_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${LIBUSB_1_LIBRARIES})

INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

option(BUILD_python "Compile pXar python interface?" OFF)
IF(BUILD_python)
MESSAGE(STATUS "Will now configure the Cython pXar core interface")
# Include the CMake script UseCython.cmake. This defines add_cython_module().
# Instruction for use can be found at the top of cmake/UseCython.cmake.
include( UseCython )

# With CMake, a clean separation can be made between the source tree and the
# build tree. When all source is compiled, as with pure C/C++, the source is
# no-longer needed in the build tree. However, with pure *.py source, the
# source is processed directly. To handle this, we reproduce the availability
# of the source files in the build tree.
add_custom_target( ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ReplicatePythonSourceTree.cmake
  ${CMAKE_CURRENT_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

if( NOT NUMPY_INCLUDE_DIR )
  find_package( PythonInterp )
  execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE _numpy_include
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  find_path( NUMPY_INCLUDE_DIR numpy/arrayobject.h
    HINTS ${_numpy_include} )
endif()
include_directories( ${NUMPY_INCLUDE_DIR}  )

set( cxx_pyx_files
  pyPxarCore/api.pyx
  pyPxarCore/stlcontainers.pyx
  pyPxarCore/xdress_extra_types.pyx
  )
set_source_files_properties( ${cxx_pyx_files}
  PROPERTIES CYTHON_IS_CXX TRUE )

cython_add_module( xdress_extra_types pyPxarCore/xdress_extra_types.pyx )
cython_add_module( stlcontainers pyPxarCore/stlcontainers.pyx )

cython_add_module( pypxar pyPxarCore/api.pyx )

target_link_libraries(pypxar ${PROJECT_NAME})

ENDIF(BUILD_python)
