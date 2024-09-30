# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tower_Defending_I_Never_Give_Up_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tower_Defending_I_Never_Give_Up_autogen.dir\\ParseCache.txt"
  "Tower_Defending_I_Never_Give_Up_autogen"
  )
endif()
