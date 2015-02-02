list(APPEND GENERATORS "TGZ;ZIP;TXZ;LZMA")

if (BUILD_PACKAGE_MSI)
  list(APPEND GENERATORS "WIX")
endif ()

if (BUILD_PACKAGE_DEB)
  list(APPEND GENERATORS "DEB")
endif ()

if (BUILD_PACKAGE_RPM)
  list(APPEND GENERATORS "RPM")
endif ()

#------------------------------------------------------------------------------
# Generic Package
#------------------------------------------------------------------------------
set(CPACK_OUTPUT_FILE_PREFIX ${PACK_BINARY_DIR})

set(CPACK_GENERATOR ${GENERATORS})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "MNMLSTC")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++11 Flyweight Pattern Implementation")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/Readme.rst")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.rst")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

# Intended for installers such as NSIS or WIX
set(CPACK_PACKAGE_INSTALL_DIRECTORY "mnmlstc/${PROJECT_NAME}")

#------------------------------------------------------------------------------
# Wix Configuration
#------------------------------------------------------------------------------
set(CPACK_WIX_CMAKE_PACKAGE_REGISTRY ${PROJECT_NAME})
set(CPACK_WIX_UPGRADE_GUID "FAB078DF-D7E5-4554-8763-A3BBDF738FDE")
set(CPACK_WIX_PRODUCT_GUID "*")
set(CPACK_WIX_PRODUCT_ICON "${PROJECT_SOURCE_DIR}/package/mnmlstc.ico")
set(CPACK_WIX_LICENSE_RTF "${PROJECT_SOURCE_DIR}/package/License.rtf")
set(CPACK_WIX_UI_BANNER "${PROJECT_SOURCE_DIR}/package/banner.bmp")
set(CPACK_WIX_UI_DIALOG "${PROJECT_SOURCE_DIR}/package/dialog.bmp")

#------------------------------------------------------------------------------
# DEB Configuration
#------------------------------------------------------------------------------
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE any)

#------------------------------------------------------------------------------
# RPM Configuration
#------------------------------------------------------------------------------
set(CPACK_RPM_PACKAGE_ARCHITECTURE noarch)
set(CPACK_RPM_PACKAGE_REQUIRES "cmake >= 3.1.0")
set(CPACK_RPM_PACKAGE_RELEASE ${PROJECT_VERSION})

include(CPack)
