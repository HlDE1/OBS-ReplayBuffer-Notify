cmake_minimum_required(VERSION 3.16...3.21)

# Change obs-plugintemplate to your plugin's name in a machine-readable format (e.g.:
# obs-myawesomeplugin) and set
project(obs-replaybuffer-notify VERSION 1.0.0)
add_library(${CMAKE_PROJECT_NAME} MODULE)

# Replace `Your Name Here` with the name (yours or your organization's) you want to see as the
# author of the plugin (in the plugin's metadata itself and in the installers)
set(PLUGIN_AUTHOR "HIDE1")

# Replace `com.example.obs-plugin-template` with a unique Bundle ID for macOS releases (used both in
# the installer and when submitting the installer for notarization)
set(MACOS_BUNDLEID "com.example.${CMAKE_PROJECT_NAME}")

# Replace `me@contoso.com` with the maintainer email address you want to put in Linux packages
set(LINUX_MAINTAINER_EMAIL "me@mymailhost.com")

# Add your custom source files here - header files are optional and only required for visibility
# e.g. in Xcode or Visual Studio
target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-main.cpp
src/Notify.cpp

)

message("OBS lib Starting")
# Import libobs as main plugin dependency
#find_package(obs REQUIRED)
include(cmake/ObsPluginHelpers.cmake)

message("OBS lib Done")
# Uncomment these lines if you want to use the OBS Frontend API in your plugin

#find_package(obs-frontend-api REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE obs-frontend-api)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE obs-frontend-api)

# Uncomment those lines if you want to use Qt in your plugin
#[[
find_qt(COMPONENTS Widgets Core)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets)
set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON)
#]]

configure_file(src/plugin-macros.h.in ${CMAKE_SOURCE_DIR}/src/plugin-macros.generated.h)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-macros.generated.h)

# /!\ TAKE NOTE: No need to edit things past this point /!\

# --- Platform-independent build settings ---

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE obs)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libobs)

# --- End of section ---



setup_plugin_target(${CMAKE_PROJECT_NAME})
