QT -= gui

CONFIG += c++20 console
CONFIG -= app_bundle

DEFINES += NDEBUG

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        car.cpp \
        cartype.cpp \
        config.cpp \
        creditcard.cpp \
        database.cpp \
        entity.cpp \
        freecarview.cpp \
        hash.cpp \
        location.cpp \
        main.cpp \
        menu.cpp \
        menuadmin.cpp \
        menuitem.cpp \
        menulogin.cpp \
        menumanagecar.cpp \
        menumanageuser.cpp \
        menuupdatecar.cpp \
        menuupdateuser.cpp \
        menuuser.cpp \
        rent.cpp \
        rentedcarview.cpp \
        rentrequest.cpp \
        service.cpp \
        try.cpp \
        user.cpp \
        utilityfunctions.cpp \
        validate.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    action.h \
    car.h \
    cartype.h \
    config.h \
    creditcard.h \
    database.h \
    entity.h \
    freecarview.h \
    hash.h \
    location.h \
    menu.h \
    menuadmin.h \
    menuitem.h \
    menulogin.h \
    menumanagecar.h \
    menumanageuser.h \
    menuupdatecar.h \
    menuupdateuser.h \
    menuuser.h \
    rent.h \
    rentedcarview.h \
    rentrequest.h \
    service.h \
    try.h \
    user.h \
    utilityfunctions.h \
    validate.h \
    variadictable.h
	
include(rbk/rbk.pri)
