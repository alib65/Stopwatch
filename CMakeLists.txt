cmake_minimum_required(VERSION 3.16)
project(Stopwatch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# --- QT SETUP ---
list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt")

find_package(Qt6 COMPONENTS Widgets QUIET)
if(Qt6_FOUND)
    message(STATUS "Found Qt 6!")
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    message(STATUS "Found Qt 5!")
endif()

# =========================================================
#  MACOS BUNDLE SETUP (FIXED)
# =========================================================

# 1. Define the icon file
set(ICON_FILE "Stopwatch.icns")

# 2. CRITICAL FIX: Tell CMake explicitly to copy this file 
#    into the 'Resources' folder inside the app bundle.
set_source_files_properties(${ICON_FILE} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
)

# 3. Create the App Bundle
add_executable(Stopwatch MACOSX_BUNDLE
    main.cpp
    resources.qrc
    ${ICON_FILE}  # It must be listed here to be copied!
)

# 4. Link the icon to the bundle info
set_target_properties(Stopwatch PROPERTIES
    MACOSX_BUNDLE_ICON_FILE ${ICON_FILE}
    MACOSX_BUNDLE_GUI_IDENTIFIER com.ali.stopwatch
)
# =========================================================

if(Qt6_FOUND)
    target_link_libraries(Stopwatch PRIVATE Qt6::Widgets)
else()
    target_link_libraries(Stopwatch PRIVATE Qt5::Widgets)
endif()