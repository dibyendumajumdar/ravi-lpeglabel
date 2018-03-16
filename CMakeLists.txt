cmake_minimum_required(VERSION 2.6)

option(USE_LUA53 "Controls whether the library will be for Lua 5.3 or Ravi, default is OFF" OFF)

SET(CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_MODULE_PATH}")

find_package(Lua REQUIRED)

message(STATUS "LUA_INCLUDE_DIR: ${LUA_INCLUDE_DIR}")
message(STATUS "LUA_LIBRARIES  : ${LUA_LIBRARIES}")

message(STATUS "LUA_INCDIR     : ${LUA_INCDIR}")
message(STATUS "LUA_LIBDIR     : ${LUA_LIBDIR}")
message(STATUS "LUA_BINDIR     : ${LUA_BINDIR}")
message(STATUS "LUALIB         : ${LUALIB}")
message(STATUS "LIBDIR (LUA_CPATH)  : ${LIBDIR}")
message(STATUS "LUADIR (LUA_PATH)   : ${LUADIR}")

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}")
INCLUDE_DIRECTORIES("${LUA_INCDIR}")
LINK_DIRECTORIES("${LUA_LIBDIR}")

SET(src 
  "${CMAKE_CURRENT_SOURCE_DIR}/lpvm.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/lpvm.h" 
  "${CMAKE_CURRENT_SOURCE_DIR}/lpcap.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/lpcap.h" 
  "${CMAKE_CURRENT_SOURCE_DIR}/lptree.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/lptree.h" 
  "${CMAKE_CURRENT_SOURCE_DIR}/lpcode.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/lpcode.h" 
  "${CMAKE_CURRENT_SOURCE_DIR}/lpprint.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/lpprint.h" 
  )

SET(luasrc 
  "${CMAKE_CURRENT_SOURCE_DIR}/test.lua"
  "${CMAKE_CURRENT_SOURCE_DIR}/testlabel.lua"
  "${CMAKE_CURRENT_SOURCE_DIR}/testrelabelparser.lua"
  "${CMAKE_CURRENT_SOURCE_DIR}/relabel.lua"
  )

# When using MSVC
IF(MSVC)
  # we want to respect the standard, and we are bored of those **** .
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE=1)
ENDIF(MSVC)

ADD_LIBRARY("lpeglabel" SHARED ${src})
set_target_properties("lpeglabel" PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES("lpeglabel" PROPERTIES
  DEFINE_SYMBOL "lpeglabel_EXPORTS"
  IMPORT_PREFIX "lib")

IF(APPLE)
  SET_TARGET_PROPERTIES("lpeglabel" PROPERTIES
    LINK_FLAGS "-undefined dynamic_lookup")
ENDIF()

INSTALL(FILES ${luasrc} DESTINATION ${LUADIR}/lpeglabel)
INSTALL(TARGETS lpeglabel
  LIBRARY DESTINATION ${LIBDIR}
  RUNTIME DESTINATION ${LUA_BINDIR})

IF(LUALIB)
  TARGET_LINK_LIBRARIES(lpeglabel ${LUALIB})
ENDIF()
