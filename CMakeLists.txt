cmake_minimum_required(VERSION 2.8.12)
project(pass_runner)

find_package(ECM 5.12.0 REQUIRED NO_MODULE)
set (CMAKE_BUILD_TYPE DEBUG)
set (CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)

find_package (Qt5 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core Quick)
find_package (KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n Service Runner TextWidgets PlasmaQuick)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(${PROJECT_NAME}_SRCS pass_runner.cpp match_actions.cpp)

add_library(${PROJECT_NAME} MODULE ${${PROJECT_NAME}_SRCS})
target_link_libraries(${PROJECT_NAME} KF5::Runner Qt5::Widgets KF5::I18n KF5::Service KF5::Plasma)

install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_LIBDIR}/qt5/plugins)
install(FILES pass_runner.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
