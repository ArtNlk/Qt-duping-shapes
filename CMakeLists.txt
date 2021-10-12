cmake_minimum_required(VERSION 3.14)

project(Qt-duping-shapes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Qml Gui Quick LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Qml Gui Quick LinguistTools REQUIRED)
find_package(Qt5QuickCompiler)

option(UPDATE_TRANSLATIONS "Update source translation (files translations/*.ts)." ON)

set(TS_FILES
    Qt-duping-shapes_ru_RU.ts
    Qt-duping-shapes_en_US.ts)

set(PROJECT_SOURCES
    main.cpp
    duplicatingshapesmodel.cpp
    duplicatingshape.cpp)

set(PROJECT_HEADERS
    duplicatingshapesmodel.h
    duplicatingshape.h)

set(PROJECT_RESOURCES
    qml.qrc)

set(TRANSLATABLES ${PROJECT_SOURCES} ${PROJECT_RESOURCES})

if(UPDATE_TRANSLATIONS)
    message(STATUS "UPDATE_TRANSLATIONS option is set.")
    qt_create_translation(QM_FILES ${TRANSLATABLES} ${TS_FILES})
    #qt_add_lupdate(Qt-csv-editor ${TS_FILES})
else()
    message(STATUS "UPDATE_TRANSLATIONS option is NOT set.")
    qt_add_translation(QM_FILES ${TS_FILES})
    #qt_add_lrelease(Qt-csv-editor ${TS_FILES} QM_FILES_OUTPUT_VARIABLE QM_FILES)
endif()
message(STATUS "QM files: " ${QM_FILES})

add_custom_target(translations DEPENDS ${QM_FILES})
set_property(DIRECTORY PROPERTY CLEAN_NO_CUSTOM TRUE)

qtquick_compiler_add_resources(RESOURCES ${PROJECT_RESOURCES})
message(STATUS "Qt RESOURCES" ${RESOURCES})

add_executable(Qt-duping-shapes
    ${PROJECT_SOURCES}
    ${RESOURCES}
    #${PROJECT_RESOURCES}
    ${PROJECT_HEADERS})

add_dependencies(Qt-duping-shapes translations)

target_link_libraries(Qt-duping-shapes
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Qml)

set_target_properties(Qt-duping-shapes PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_import_qml_plugins(Qt-duping-shapes)
endif()
#installation
include(DeployQt4)

set(CMAKE_INSTALL_PREFIX "D:/Programs/Qt-duping-shapes/" )
#set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} )
get_property(LIB_QTCORE_PATH TARGET Qt${QT_VERSION_MAJOR}::Core PROPERTY IMPORTED_LOCATION_RELEASE)
get_property(LIB_QTQUICK_PATH TARGET Qt${QT_VERSION_MAJOR}::Quick PROPERTY IMPORTED_LOCATION_RELEASE)
get_property(LIB_QTQML_PATH TARGET Qt${QT_VERSION_MAJOR}::Qml PROPERTY IMPORTED_LOCATION_RELEASE)
get_property(LIB_QTNETWORK_PATH TARGET Qt${QT_VERSION_MAJOR}::Network PROPERTY IMPORTED_LOCATION_RELEASE)
get_property(LIB_QTGUI_PATH TARGET Qt${QT_VERSION_MAJOR}::Gui PROPERTY IMPORTED_LOCATION_RELEASE)

get_filename_component(QT_LIBRARY_DIR "${LIB_QTCORE_PATH}" DIRECTORY)
get_filename_component(QT_PATH "${LIB_QTCORE_PATH}" PATH)
get_filename_component(QT_PATH "${QT_PATH}" PATH)

message(STATUS "Qt path" ${QT_PATH})
install(DIRECTORY "${QT_PATH}/plugins/platforms" DESTINATION bin)
install(TARGETS Qt-duping-shapes RUNTIME DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION translations)
#install(FILES ${PROJECT_RESOURCES} DESTINATION bin)

set(EXE_PATH bin/Qt-duping-shapes${CMAKE_EXECUTABLE_SUFFIX})

message(STATUS "Path: " ${LIB_QTNETWORK_PATH})

install(FILES "${LIB_QTCORE_PATH}" DESTINATION bin)
install(FILES "${LIB_QTQUICK_PATH}" DESTINATION bin)
install(FILES "${LIB_QTQML_PATH}" DESTINATION bin)
install(FILES "${LIB_QTNETWORK_PATH}" DESTINATION bin)
install(FILES "${LIB_QTGUI_PATH}" DESTINATION bin)

message(STATUS "Installing to " ${CMAKE_INSTALL_PREFIX} " / " ${EXE_PATH})

install_qt4_executable(
    "${EXE_PATH}"     #исполняемый файл
    ""                  #модули
    ""                  #библиотеки
    ${QT_LIBRARY_DIR} )#каталоги

