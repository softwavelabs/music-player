TEMPLATE = app
TARGET = main
QT += quick quickcontrols2 widgets multimedia

SOURCES += \
    main.cpp \
    musicplayer.cpp

RESOURCES += \
    icons/icons.qrc \
    imagine-assets/imagine-assets.qrc \
    qtquickcontrols2.conf \
    main.qml \
    images/

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/imagine/musicplayer
INSTALLS += target

HEADERS += \
    musicplayer.h

# Add architecture flags for macOS (targeting x86_64)
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15   # Optional: specifies minimum macOS version
QMAKE_CXXFLAGS += -arch x86_64          # Add architecture flag for x86_64
QMAKE_LFLAGS += -arch x86_64            # Ensure linking for x86_64

# To target both arm64 and x86_64 (Universal binary)
# Uncomment this if you want a universal build (both arm64 and x86_64)
# QMAKE_CXXFLAGS += -arch x86_64 -arch arm64
# QMAKE_LFLAGS += -arch x86_64 -arch arm64
