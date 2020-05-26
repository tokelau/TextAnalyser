QT += quick qml
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
    textProcessor/include_1.0/docx/duckx.cpp \
    textProcessor/include_1.0/docx/iconvlite.cpp \
    textProcessor/include_1.0/docx/pugixml.cpp \
    textProcessor/include_1.0/docx/zip.c

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

RC_ICONS = iconkek.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    fileitem.h \
    files.h \
    fileparams.h \
    dictitem.h \
    dicts.h \
    wrappers/dictwrap.h \
    wrappers/filewrap.h \
    buttonitem.h \
    textProcessor/include_1.0/docx/duckx.hpp \
    textProcessor/include_1.0/docx/iconvlite.h \
    textProcessor/include_1.0/docx/miniz.h \
    textProcessor/include_1.0/docx/pugiconfig.hpp \
    textProcessor/include_1.0/docx/pugixml.hpp \
    textProcessor/include_1.0/docx/zip.h \
    wrappers/dictwrap.h \
    wrappers/filewrap.h \
    buttonitem.h \
    dictitem.h \
    dicts.h \
    fileitem.h \
    fileparams.h \
    files.h


DISTFILES += \
    analyse.qml \
    actions/editTextActions.qml \
    actions/editDictsActions.qml ] \
    actions/editDocxTextAction.qml \
    actions/editDocxTextAction.qml


win32: LIBS += -L$$PWD/textProcessor/bin/Debug/ -lTextProcessor-1.0

INCLUDEPATH += $$PWD/textProcessor/include_1.0
DEPENDPATH += $$PWD/textProcessor/include_1.0

win32: LIBS += -L$$PWD/./ -llibhunspell-1.7-0

INCLUDEPATH += $$PWD/textProcessor/include_1.0/hunspell
DEPENDPATH += $$PWD/textProcessor/include_1.0/hunspell
