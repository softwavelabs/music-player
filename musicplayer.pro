TEMPLATE = app
TARGET = musicplayer
QT += quick quickcontrols2

SOURCES += \
    musicplayer.cpp

RESOURCES += \
    icons/icons.qrc \
    imagine-assets/imagine-assets.qrc \
    qtquickcontrols2.conf \
    musicplayer.qml \
    images/

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/imagine/musicplayer
INSTALLS += target
