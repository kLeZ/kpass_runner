project(plasma-pass_runner)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(QT_MIN_VERSION "5.4.0")
set(KF5_MIN_VERSION "5.14.0")
set(INSTALL_SDDM_THEME TRUE)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Widgets )
find_package(ECM 1.8.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Runner)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMPackageConfigHelpers)
include(ECMMarkNonGuiExecutable)
include(CMakePackageConfigHelpers)
include(WriteBasicConfigVersionFile)
include(CheckIncludeFiles)
include(FeatureSummary)
include(ECMOptionalAddSubdirectory)

set(pass_runner_SRCS pass_runner.cpp)

add_library(krunner_pass_runner MODULE ${pass_runner_SRCS})
target_link_libraries(krunner_pass_runner KF5::Runner)

install(TARGETS krunner_pass_runner DESTINATION ${KDE_INSTALL_PLUGINDIR})

install(FILES pass_runner.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
