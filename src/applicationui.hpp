#ifndef __APPLICATION_UI_HPP__
#define __APPLICATION_UI_HPP__

#include "settings.hpp"
#include "ttrssmanager.hpp"

#include <QtCore/QObject>

namespace bb {
	namespace cascades {
		class Application;
	}
}

class ApplicationUI : public QObject {

    Q_OBJECT

public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() {}

private:
    Settings		_settings;
    TTRSSManager	_manager;
};

#endif // __APPLICATION_UI_HPP__
