APP_NAME = tt_rss

CONFIG += qt warn_on cascades10
LIBS   += -lbbdata -lbbsystem -lbb

QT += network

include(config.pri)

TRANSLATIONS =  $$quote($${TARGET}.ts) \
				$$quote($${TARGET}_fr.ts)