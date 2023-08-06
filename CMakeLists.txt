cmake_minimum_required(VERSION 3.16)

project(simple-wireguard-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

include_directories("../libssh2-build/include")
add_library(ssh2 SHARED IMPORTED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set_property(TARGET ssh2 PROPERTY IMPORTED_LOCATION ../libssh2-build/lib-x86_64-linux/libssh2.so)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set_property(TARGET ssh2 PROPERTY IMPORTED_LOCATION ../libssh2-build/lib-armeabi-v7a/libssh2.so)
endif()

qt_standard_project_setup()

qt_add_executable(simple-wireguard
    main.cpp
)

qt_add_qml_module(simple-wireguard
    URI simple-wireguard-gui
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES ServerListPage.qml
    QML_FILES AddServerPage.qml
    SOURCES sshcommands.h sshcommands.cpp
    SOURCES serverlistmodel.h serverlistmodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(simple-wireguard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.simple-wireguard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(simple-wireguard
    PRIVATE Qt6::Quick
    ssh2
)

include(GNUInstallDirs)
install(TARGETS simple-wireguard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
