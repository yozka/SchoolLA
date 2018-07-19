QT += quick quickcontrols2 network

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    source/API/Models/ssAbstractJsonListModel.cpp \
    source/API/Models/ssBaseListModel.cpp \
    source/API/Models/ssDetailsModel.cpp \
    source/API/Models/ssItem.cpp \
    source/API/Models/ssJsonListModel.cpp \
    source/API/Models/ssPagination.cpp \
    source/API/Models/ssRequests.cpp \
    source/API/ssApibase.cpp \
    source/API/ssUtils.cpp \
    source/Sevice/slaServiceAPI.cpp \
    source/API/Models/ssAbstractJsonListModel.cpp \
    source/API/Models/ssBaseListModel.cpp \
    source/API/Models/ssDetailsModel.cpp \
    source/API/Models/ssItem.cpp \
    source/API/Models/ssJsonListModel.cpp \
    source/API/Models/ssPagination.cpp \
    source/API/Models/ssRequests.cpp \
    source/API/ssApibase.cpp \
    source/API/ssUtils.cpp \
    source/Sevice/slaServiceAPI.cpp \
    main.cpp

RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/API/Models/ssAbstractJsonListModel.h \
    source/API/Models/ssBaseListModel.h \
    source/API/Models/ssDetailsModel.h \
    source/API/Models/ssItem.h \
    source/API/Models/ssJsonListModel.h \
    source/API/Models/ssPagination.h \
    source/API/Models/ssRequests.h \
    source/API/ssApibase.h \
    source/API/ssUtils.h \
    source/Sevice/slaServiceAPI.h \
    source/API/Models/ssAbstractJsonListModel.h \
    source/API/Models/ssBaseListModel.h \
    source/API/Models/ssDetailsModel.h \
    source/API/Models/ssItem.h \
    source/API/Models/ssJsonListModel.h \
    source/API/Models/ssPagination.h \
    source/API/Models/ssRequests.h \
    source/API/ssApibase.h \
    source/API/ssUtils.h \
    source/Sevice/slaServiceAPI.h

