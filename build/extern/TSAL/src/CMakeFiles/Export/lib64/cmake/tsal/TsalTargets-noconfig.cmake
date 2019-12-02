#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tsal::tsal" for configuration ""
set_property(TARGET tsal::tsal APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(tsal::tsal PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib64/libtsal.so"
  IMPORTED_SONAME_NOCONFIG "libtsal.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS tsal::tsal )
list(APPEND _IMPORT_CHECK_FILES_FOR_tsal::tsal "${_IMPORT_PREFIX}/lib64/libtsal.so" )

# Import target "tsal::midifile" for configuration ""
set_property(TARGET tsal::midifile APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(tsal::midifile PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib64/libmidifile.so"
  IMPORTED_SONAME_NOCONFIG "libmidifile.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS tsal::midifile )
list(APPEND _IMPORT_CHECK_FILES_FOR_tsal::midifile "${_IMPORT_PREFIX}/lib64/libmidifile.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
