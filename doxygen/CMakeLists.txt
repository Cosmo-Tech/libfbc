# Dependencies
find_package(Doxygen REQUIRED)

macro(csmAddDoxygen a_Name a_DstDir a_SrcFilesOrDirs a_WithSources)
  set(DOXYGEN_PROJECT ${a_Name})
  set(DOXYGEN_PROJECT_SRC)
  foreach(fileOrDir ${a_SrcFilesOrDirs})
    set(DOXYGEN_PROJECT_SRC "${DOXYGEN_PROJECT_SRC} \"${fileOrDir}\"")
  endforeach()
  set(DOXYGEN_WITH_SOURCES ${a_WithSources})

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.config.in
    ${CMAKE_CURRENT_BINARY_DIR}/${a_DstDir}.config
    @ONLY)

  # list the source dependencies
  set(deps)
  foreach(fileOrDir ${a_SrcFilesOrDirs})
    if(IS_DIRECTORY "${fileOrDir}")
      # all the files in the directory are dependencies
      file(GLOB_RECURSE files
        ${fileOrDir}/*.h
        ${fileOrDir}/*.c
        ${fileOrDir}/*.hxx
        ${fileOrDir}/*.cxx)
    else()
      # the file is itself a dependency
      set(files "${fileOrDir}")
    endif()
    list(APPEND deps ${files})
  endforeach()
  list(APPEND deps ${CMAKE_CURRENT_SOURCE_DIR}/header.html)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${a_Name}/html/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/${a_Name}/xml/index.xml
    COMMAND ${DOXYGEN} ${CMAKE_CURRENT_BINARY_DIR}/${a_DstDir}.config
    COMMENT "Generating Doxygen html output for ${a_DstDir}..."
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${a_DstDir}.config ${deps})

  add_custom_target(DocDoxygen${a_Name} ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${a_Name}/html/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/${a_Name}/xml/index.xml)
endmacro()

option(FBC_DOXYGEN_WITH_SOURCES "Build the Doxygen documentation with sources" ON)
mark_as_advanced(FBC_DOXYGEN_WITH_SOURCES)

# Configure documentation for the Engine
if(FBC_DOXYGEN_WITH_SOURCES)
  csmAddDoxygen("doxygen" "WithSources" "${LIBFBC_SOURCE_DIR}/src/fbc" YES)
else()
  csmAddDoxygen("doxygen" "WithoutSources" "${LIBFBC_SOURCE_DIR}/src/fbc" NO)
endif()
