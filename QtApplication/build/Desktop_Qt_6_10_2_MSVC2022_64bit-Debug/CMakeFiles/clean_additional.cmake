# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtApplication_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtApplication_autogen.dir\\ParseCache.txt"
  "QtApplication_autogen"
  )
endif()
