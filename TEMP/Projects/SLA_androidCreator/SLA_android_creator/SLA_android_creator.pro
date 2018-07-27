QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    ../../../Shared/Source/API/Models/ssAbstractJsonListModel.cpp \
    ../../../Shared/Source/API/Models/ssBaseListModel.cpp \
    ../../../Shared/Source/API/Models/ssDetailsModel.cpp \
    ../../../Shared/Source/API/Models/ssItem.cpp \
    ../../../Shared/Source/API/Models/ssJsonListModel.cpp \
    ../../../Shared/Source/API/Models/ssPagination.cpp \
    ../../../Shared/Source/API/Models/ssRequests.cpp \
    ../../../Shared/Source/API/ssApibase.cpp \
    ../../../Shared/Source/API/ssUtils.cpp \
    ../../../Shared/Source/Sevice/slaServiceAPI.cpp \
    ../../../Shared/Source/API/Models/ssAbstractJsonListModel.cpp \
    ../../../Shared/Source/API/Models/ssBaseListModel.cpp \
    ../../../Shared/Source/API/Models/ssDetailsModel.cpp \
    ../../../Shared/Source/API/Models/ssItem.cpp \
    ../../../Shared/Source/API/Models/ssJsonListModel.cpp \
    ../../../Shared/Source/API/Models/ssPagination.cpp \
    ../../../Shared/Source/API/Models/ssRequests.cpp \
    ../../../Shared/Source/API/ssApibase.cpp \
    ../../../Shared/Source/API/ssUtils.cpp \
    ../../../Shared/Source/Sevice/slaServiceAPI.cpp

RESOURCES += \
    ../../../Shared/QML/Resource.qrc \
    ../../../Shared/QML/Resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../../Shared/Source/API/Models/ssAbstractJsonListModel.h \
    ../../../Shared/Source/API/Models/ssBaseListModel.h \
    ../../../Shared/Source/API/Models/ssDetailsModel.h \
    ../../../Shared/Source/API/Models/ssItem.h \
    ../../../Shared/Source/API/Models/ssJsonListModel.h \
    ../../../Shared/Source/API/Models/ssPagination.h \
    ../../../Shared/Source/API/Models/ssRequests.h \
    ../../../Shared/Source/API/ssApibase.h \
    ../../../Shared/Source/API/ssUtils.h \
    ../../../Shared/Source/Sevice/slaServiceAPI.h \
    ../../../Shared/Source/API/Models/ssAbstractJsonListModel.h \
    ../../../Shared/Source/API/Models/ssBaseListModel.h \
    ../../../Shared/Source/API/Models/ssDetailsModel.h \
    ../../../Shared/Source/API/Models/ssItem.h \
    ../../../Shared/Source/API/Models/ssJsonListModel.h \
    ../../../Shared/Source/API/Models/ssPagination.h \
    ../../../Shared/Source/API/Models/ssRequests.h \
    ../../../Shared/Source/API/ssApibase.h \
    ../../../Shared/Source/API/ssUtils.h \
    ../../../Shared/Source/Sevice/slaServiceAPI.h

DISTFILES += \
    ../../../Shared/QML/GradePage.qml \
    ../../../Shared/QML/GradesList.qml \
    ../../../Shared/QML/main.qml \
    ../../../Shared/QML/SchoolPage.qml \
    ../../../Shared/QML/touch.bat \
    ../../../Shared/QML/ConversationPage.qml \
    ../../../Shared/QML/GradePage.qml \
    ../../../Shared/QML/GradesList.qml \
    ../../../Shared/QML/main.qml \
    ../../../Shared/QML/SchoolPage.qml
