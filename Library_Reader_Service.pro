QT       += core gui sql \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ValidateInput.cpp \
    abstractcalc.cpp \
    abv_tree.cpp \
    book_data.cpp \
    boyer_moore.cpp \
    calcfactory.cpp \
    calcfactoryimpl.cpp \
    calculationfacade.cpp \
    events.cpp \
    guapcalc.cpp \
    hashtable.cpp \
    jmax_limcalc.cpp \
    linked_list.cpp \
    main.cpp \
    mainwindow.cpp \
    ownerdialog.cpp \
    portaldialog.cpp \
    registerdialog.cpp \
    te_librarycalc.cpp \
    ted_talkscalc.cpp \
    unza.cpp

HEADERS += \
    ValidateInput.h \
    abstractcalc.h \
    abv_tree.h \
    book_data.h \
    boyer_moore.h \
    calcfactory.h \
    calcfactoryimpl.h \
    calculationfacade.h \
    events.h \
    guapcalc.h \
    hashtable.h \
    headers.h \
    jmax_limcalc.h \
    linked_list.h \
    mainwindow.h \
    ownerdialog.h \
    portaldialog.h \
    registerdialog.h \
    te_librarycalc.h \
    ted_talkscalc.h \
    unza.h

FORMS += \
    mainwindow.ui \
    ownerdialog.ui \
    portaldialog.ui \
    registerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

