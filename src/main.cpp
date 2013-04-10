#include "applicationui.hpp"

#include "data/category.hpp"

#include <bb/cascades/Application>

#include <QtCore/QLocale>
#include <QtCore/QTranslator>

// include JS Debugger / CS Profiler enabler
// this feature is enabled by default in the debug build only
#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

#ifdef QT_DEBUG
void standardOutput(QtMsgType /*type*/, const char* msg) {
	fprintf(stdout, "%s\n", msg);
	fflush(stdout);
}
#endif // QT_DEBUG

Q_DECL_EXPORT int main(int argc, char **argv) {
	qRegisterMetaType<Category>("Category");

    Application app(argc, argv);

#ifdef QT_DEBUG
    qInstallMsgHandler(standardOutput);
#endif // QT_DEBUG

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString("tt_rss_%1").arg(locale_string);
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator(&translator);
    }

    new ApplicationUI(&app);
    return Application::exec();
}

