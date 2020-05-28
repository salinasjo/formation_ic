#-------------------------------------------------
#
# Project created by QtCreator 2020-05-07T19:04:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = droneVulkan
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        form/drawer.cpp \
	form/droneformwindow.cpp \
		form/missionwindow.cpp \
        form/dronewindow.cpp \
        form/loginwindow.cpp \
        form/trajectoryWindow.cpp \
        main.cpp \
        form/mainwindow.cpp \
        src/Admin.cpp \
        src/Commander.cpp \
        src/ControlPoint.cpp \
        src/DiscreteMap.cpp \
        src/Drone.cpp \
        src/DroneType.cpp \
        src/FileDump.cpp \
        src/MissionProcess.cpp \
        src/MissionType.cpp \
        src/Operator.cpp \
        src/Point.cpp \
		src/SerializableCollection.cpp \
        src/Trajectory.cpp \
        src/User.cpp \
        src/WingType.cpp \
        src/mapinfo.cpp \
        src/test.cpp

HEADERS += \
        form/drawer.h \
	form/droneformwindow.h \
        form/dronewindow.h \
        form/loginwindow.h \
        form/mainwindow.h \
		form/missionwindow.h \
        form/trajectoryWindow.h \
        include/Admin.h \
        include/Commander.h \
        include/ControlPoint.h \
        include/DiscreteMap.h \
        include/Drone.h \
        include/DroneType.h \
        include/FileDump.h \
		include/ISerializable.h \
        include/MissionProcess.h \
        include/MissionType.h \
        include/Operator.h \
        include/Point.h \
        include/Trajectory.h \
        include/User.h \
        include/WingType.h \
        include/mapinfo.h \
        include/test.h \
		include/SerializableCollection.h

FORMS += \
        form/drawer.ui \
	form/droneformwindow.ui \
        form/dronewindow.ui \
        form/loginwindow.ui \
        form/mainwindow.ui \
		form/missionwindow.ui \
        form/trajectoryWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
