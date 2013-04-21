#include "feedmanager.hpp"

#include "ttrssmanager.hpp"

#include "data/category.hpp"
#include "data/feed.hpp"

namespace ttrss {
	FeedManager::FeedManager(TTRSSManager* mainManager) : bb::cascades::GroupDataModel(QStringList() << "title"), _mainManager(mainManager) {
	}

	FeedManager::~FeedManager() {
	}
}
