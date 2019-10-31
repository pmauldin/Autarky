FIND_PATH(ASSIMP_INCLUDE_DIR assimp/mesh.h
        /usr/include
        /usr/local/include
        /opt/local/include
        ${CMAKE_SOURCE_DIR}/includes
        Z:/Dev/Libraries/OpenGL/Include
        )
FIND_LIBRARY(ASSIMP_LIBRARY assimp
        /usr/lib64
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        ${CMAKE_SOURCE_DIR}/lib
        Z:/Dev/Libraries/OpenGL/Libs
        )

IF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
    SET( ASSIMP_FOUND TRUE )
    SET( ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
IF(ASSIMP_FOUND)
    IF(NOT ASSIMP_FIND_QUIETLY)
        MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
    ENDIF(NOT ASSIMP_FIND_QUIETLY)
ELSE(ASSIMP_FOUND)
    IF(ASSIMP_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find libASSIMP")
    ENDIF(ASSIMP_FIND_REQUIRED)
ENDIF(ASSIMP_FOUND)