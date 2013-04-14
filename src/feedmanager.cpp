#include "feedmanager.hpp"

#include "ttrssmanager.hpp"

#include "data/category.hpp"
#include "data/feed.hpp"

#include <QtCore/QDebug>

namespace ttrss {
	FeedManager::FeedManager(TTRSSManager* mainManager) : bb::cascades::GroupDataModel(QStringList() << "title"), _mainManager(mainManager) {
	}

	FeedManager::~FeedManager() {
	}

	void FeedManager::filterOnCategory(int /*categoryId*/) {
		// TODO: filter on category
	}

	void FeedManager::resetCategoryFilter() {
		// TODO: reset filter
	}
}
