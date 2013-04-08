#ifndef __APPLICATION_UI_HPP__
#define __APPLICATION_UI_HPP__

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
};

#endif // __APPLICATION_UI_HPP__
