#project(libPSI)


##############################################
##                 Link NTL                  #
##############################################
set(NTL_Lib_Dirs "${NTL_Dirs}src/")
set(NTL_Include_Dirs "${NTL_Dirs}include/")

# default location for NTL
#set(NTL_LIB "${NTL_Lib_Dirs}nnnnlibntl.a")


#if(NOT EXISTS "${NTL_LIB}")
  # we failed to find it, try using find_library
  find_library(
    NTL_LIB
    NAMES ntl libntl.a
    PATHS "${NTL_Lib_Dirs}")

  # if we still cant fint it, throw an error
  if(NOT NTL_LIB)
	if(EXISTS "${NTL_Lib_Dirs}libntl.a")
		set(NTL_LIB "${NTL_Lib_Dirs}libntl.a")
	else()
	   Message(${NTL_LIB})
		message(FATAL_ERROR "Failed to find NTL at ${NTL_Lib_Dirs} or at system locations." )
	endif()
  endif()
#endif()


message(STATUS "NTL  ${NTL_LIB}")
message(STATUS "NTL  ${NTL_Include_Dirs}")
message(STATUS "NTL  ${NTL_Lib_Dirs}")
##############################################
##                 Link GMP                  #
##############################################
set(GMP_Lib_Dirs "${GMP_Dirs}src/")
set(GMP_Include_Dirs "${GMP_Dirs}include/")
  find_library(
    GMP_LIB
    NAMES gmp libgmp.a
    PATHS "${GMP_Lib_Dirs}")

  # if we still cant fint it, throw an error
  if(NOT GMP_LIB)
	if(EXISTS "${GMP_Lib_Dirs}libgmp.a")
		set(GMP_LIB "${GMP_Lib_Dirs}libgmp.a")
	else()
	   Message(${GMP_LIB})
		message(FATAL_ERROR "Failed to find GMP at ${GMP_Lib_Dirs} or at system locations." )
	endif()
  endif()
#endif()


message(STATUS "GMP  ${GMP_LIB}")
message(STATUS "GMP  ${GMP_Include_Dirs}")
message(STATUS "GMP  ${GMP_Lib_Dirs}")

#############################################
#                 Link libOTe               #
#############################################


find_library(
    libOTe_LIB
    NAMES libOTe
    HINTS "${libOTe_Dirs}/lib/")

find_library(
    cryptoTools_LIB
    NAMES cryptoTools
    HINTS "${libOTe_Dirs}/lib/")


#############################################
#              Build libPSI                #
#############################################

file(GLOB_RECURSE SRCS *.cpp)


add_library(libPSI ${SRCS})


target_include_directories(libPSI PUBLIC ${NTL_Include_Dirs})
target_include_directories(libPSI PUBLIC ${GMP_Include_Dirs})
target_include_directories(libPSI PUBLIC ${CMAKE_SOURCE_DIR}/libOTe)
target_include_directories(libPSI PUBLIC ${CMAKE_SOURCE_DIR}/libOTe/cryptoTools)
target_include_directories(libPSI PUBLIC ${CMAKE_SOURCE_DIR}/libPSI)
target_include_directories(libPSI PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(libPSI libOTe libTests ${NTL_LIB} ${GMP_LIB})
