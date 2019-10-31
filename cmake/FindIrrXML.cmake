# Find IrrXMl from irrlicht project
#
# Find LibIrrXML headers and library
#
#   IRRXML_FOUND          - IrrXML found
#   IRRXML_INCLUDE_DIR    - Headers location
#   IRRXML_LIBRARY        - IrrXML main library

find_path(IRRXML_INCLUDE_DIR irrXML.h
    PATH_SUFFIXES irrlicht irrXML PATHS Z:/Dev/Libraries/OpenGL/Include)
find_library(IRRXML_LIBRARY IrrXML PATHS Z:/Dev/Libraries/OpenGL/Libs)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IrrXML REQUIRED_VARS IRRXML_INCLUDE_DIR IRRXML_LIBRARY)

mark_as_advanced(IRRXML_INCLUDE_DIR IRRXML_LIBRARY)
