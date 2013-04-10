# Auto-generated by IDE. Any changes made by user will be lost!
BASEDIR =  $$quote($$_PRO_FILE_PWD_)

device {
    CONFIG(debug, debug|release) {
        SOURCES +=  $$quote($$BASEDIR/src/applicationui.cpp) \
                 $$quote($$BASEDIR/src/main.cpp) \
                 $$quote($$BASEDIR/src/packets/apacket.cpp) \
                 $$quote($$BASEDIR/src/packets/getcategories.cpp) \
                 $$quote($$BASEDIR/src/packets/login.cpp) \
                 $$quote($$BASEDIR/src/settings.cpp) \
                 $$quote($$BASEDIR/src/ttrssmanager.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/applicationui.hpp) \
                 $$quote($$BASEDIR/src/packets/apacket.hpp) \
                 $$quote($$BASEDIR/src/packets/getcategories.hpp) \
                 $$quote($$BASEDIR/src/packets/login.hpp) \
                 $$quote($$BASEDIR/src/settings.hpp) \
                 $$quote($$BASEDIR/src/ttrssmanager.hpp)
    }

    CONFIG(release, debug|release) {
        SOURCES +=  $$quote($$BASEDIR/src/applicationui.cpp) \
                 $$quote($$BASEDIR/src/main.cpp) \
                 $$quote($$BASEDIR/src/packets/apacket.cpp) \
                 $$quote($$BASEDIR/src/packets/getcategories.cpp) \
                 $$quote($$BASEDIR/src/packets/login.cpp) \
                 $$quote($$BASEDIR/src/settings.cpp) \
                 $$quote($$BASEDIR/src/ttrssmanager.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/applicationui.hpp) \
                 $$quote($$BASEDIR/src/packets/apacket.hpp) \
                 $$quote($$BASEDIR/src/packets/getcategories.hpp) \
                 $$quote($$BASEDIR/src/packets/login.hpp) \
                 $$quote($$BASEDIR/src/settings.hpp) \
                 $$quote($$BASEDIR/src/ttrssmanager.hpp)
    }
}

simulator {
    CONFIG(debug, debug|release) {
        SOURCES +=  $$quote($$BASEDIR/src/applicationui.cpp) \
                 $$quote($$BASEDIR/src/main.cpp) \
                 $$quote($$BASEDIR/src/packets/apacket.cpp) \
                 $$quote($$BASEDIR/src/packets/getcategories.cpp) \
                 $$quote($$BASEDIR/src/packets/login.cpp) \
                 $$quote($$BASEDIR/src/settings.cpp) \
                 $$quote($$BASEDIR/src/ttrssmanager.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/applicationui.hpp) \
                 $$quote($$BASEDIR/src/packets/apacket.hpp) \
                 $$quote($$BASEDIR/src/packets/getcategories.hpp) \
                 $$quote($$BASEDIR/src/packets/login.hpp) \
                 $$quote($$BASEDIR/src/settings.hpp) \
                 $$quote($$BASEDIR/src/ttrssmanager.hpp)
    }
}

INCLUDEPATH +=  $$quote($$BASEDIR/src/packets) \
         $$quote($$BASEDIR/src)

CONFIG += precompile_header

PRECOMPILED_HEADER =  $$quote($$BASEDIR/precompiled.h)

lupdate_inclusion {
    SOURCES +=  $$quote($$BASEDIR/../src/*.c) \
             $$quote($$BASEDIR/../src/*.c++) \
             $$quote($$BASEDIR/../src/*.cc) \
             $$quote($$BASEDIR/../src/*.cpp) \
             $$quote($$BASEDIR/../src/*.cxx) \
             $$quote($$BASEDIR/../assets/*.qml) \
             $$quote($$BASEDIR/../assets/*.js) \
             $$quote($$BASEDIR/../assets/*.qs)

    HEADERS +=  $$quote($$BASEDIR/../src/*.h) \
             $$quote($$BASEDIR/../src/*.h++) \
             $$quote($$BASEDIR/../src/*.hh) \
             $$quote($$BASEDIR/../src/*.hpp) \
             $$quote($$BASEDIR/../src/*.hxx)
}

TRANSLATIONS =  $$quote($${TARGET}.ts)
