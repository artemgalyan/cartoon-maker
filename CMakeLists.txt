cmake_minimum_required(VERSION 3.22)
project(cartoon_maker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "<Path to Qt>/QT/6.3.1/mingw_64")

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)


add_executable(cartoon_maker main.cpp entities/skeleton/point/point.h
    entities/skeleton/point/MainPoint.cpp entities/skeleton/point/MainPoint.h
    entities/skeleton/point/SidePoint.cpp entities/skeleton/point/SidePoint.h
    entities/skeleton/Skeleton.cpp entities/skeleton/Skeleton.h entities/body/Body.cpp
    entities/body/Body.h logic/images/Image.cpp logic/images/Image.h
    entities/body/factory/BodyFactory.cpp entities/body/factory/BodyFactory.h
    entities/skeleton/point/PointSnapshot.cpp entities/skeleton/point/PointSnapshot.h
    entities/skeleton/point/point_utils.h entities/skeleton/SkeletonSnapshot.cpp
    entities/skeleton/SkeletonSnapshot.h entities/body/BodySnapshot.cpp
    entities/body/BodySnapshot.h entities/Frame.cpp entities/Frame.h
    entities/Cartoon.cpp entities/Cartoon.h
    ui/testwidget.cpp ui/testwidget.h ui/testwidget.ui entities/skeleton/point/point.cpp res.qrc
    ui/cartooneditor.h ui/cartooneditor.cpp ui/cartooneditor.ui ui/framewidget.h ui/framewidget.cpp ui/framewidget.ui
    ui/frameview.h ui/frameview.cpp)

target_link_libraries(cartoon_maker
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )

if (WIN32)
  set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
  if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
    set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
      set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    endif ()
  endif ()
  if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
  endif ()
  foreach (QT_LIB Core Gui Widgets)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
  endforeach (QT_LIB)
endif ()
