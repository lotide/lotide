# Install script for directory: /home/duckonomy/Development/LoTide/lotide/extern/TSAL/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local/")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/src/libtsal.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so"
         OLD_RPATH "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/extern/portaudio:/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/extern:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libtsal.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmidifile.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmidifile.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmidifile.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/extern/libmidifile.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmidifile.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmidifile.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmidifile.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal/TsalTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal/TsalTargets.cmake"
         "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/src/CMakeFiles/Export/lib64/cmake/tsal/TsalTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal/TsalTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal/TsalTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal" TYPE FILE FILES "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/src/CMakeFiles/Export/lib64/cmake/tsal/TsalTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal" TYPE FILE FILES "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/src/CMakeFiles/Export/lib64/cmake/tsal/TsalTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tsal" TYPE FILE FILES
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/AudioBuffer.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Buffer.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/ChannelDevice.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Channel.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Compressor.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Delay.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/EffectChain.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Effect.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Envelope.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/InputDevice.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Instrument.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/MidiNotes.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/MidiParser.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Mixer.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Oscillator.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/OutputDevice.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/PolySynth.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/ProgressOctave.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/RouteDevice.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Sequencer.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/SoundFont.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Synth.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/ThreadSynth.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Timing.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/tsal.hpp"
    "/home/duckonomy/Development/LoTide/lotide/extern/TSAL/include/Util.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/tsal" TYPE FILE FILES
    "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/src/TsalConfig.cmake"
    "/home/duckonomy/Development/LoTide/lotide/build/extern/TSAL/src/TsalConfigVersion.cmake"
    )
endif()

