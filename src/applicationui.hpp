#ifndef __APPLICATION_UI_HPP__
#define __APPLICATION_UI_HPP__

#include "articlemanager.hpp"
#include "feedmanager.hpp"
#include "filteredfeedmanager.hpp"
#include "settings.hpp"
#include "ttrssmanager.hpp"

#include <QtCore/QObject>

namespace bb {
	namespace cascades {
		class Application;
	}
}

namespace ttrss {
	class ApplicationUI : public QObject {

		Q_OBJECT

	public:
		ApplicationUI(bb::cascades::Application *app);
		virtual ~ApplicationUI() {}

	private:
		ArticleManager		_articleManager;
		FeedManager			_feedManager;
		FilteredFeedManager	_filteredFeedManager;
		Settings			_settings;
		TTRSSManager		_manager;
	};
}

#endif // __APPLICATION_UI_HPP__
