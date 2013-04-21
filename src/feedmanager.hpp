#ifndef __FEED_MANAGER_HPP__
#define __FEED_MANAGER_HPP__

namespace ttrss {
	class TTRSSManager;
}

#include <bb/cascades/GroupDataModel>

namespace ttrss {
	class FeedManager : public bb::cascades::GroupDataModel {

		Q_OBJECT

	public:
		FeedManager(TTRSSManager* mainManager);
		virtual ~FeedManager();

	private:
		TTRSSManager*	_mainManager;
	};
}

#endif // __FEED_MANAGER_HPP__
