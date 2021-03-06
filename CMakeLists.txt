CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "DEBUG")
  #SET(CMAKE_BUILD_TYPE "RELEASE")
  #SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
  #SET(CMAKE_BUILD_TYPE "MINSIZEREL")
ENDIF()

FIND_PACKAGE(PythonLibs 2.7 REQUIRED)
MESSAGE("${PYTHON_LIBRARY}")
MESSAGE("${PYTHON_INCLUDE_DIR}")

find_package(CUDA QUIET REQUIRED)
set(
    CUDA_NVCC_FLAGS
    ${CUDA_NVCC_FLAGS};
    -shared -Xcompiler -fPIC
)


FIND_PACKAGE(Boost 1.45.0)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" "/usr/include/python2.7/")
  SET(Boost_USE_STATIC_LIBS OFF)
  SET(Boost_USE_MULTITHREADED ON)
  SET(Boost_USE_STATIC_RUNTIME OFF)
  FIND_PACKAGE(Boost 1.45.0 COMPONENTS python)

  CUDA_ADD_LIBRARY(yay SHARED yay.cxx)
  TARGET_LINK_LIBRARIES(yay ${Boost_LIBRARIES} "${PYTHON_LIBRARY}" "/usr/local/lib/libboost_numpy.so")
ELSEIF(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS("-Wall")
ELSE()
  MESSAGE(FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
ENDIF()